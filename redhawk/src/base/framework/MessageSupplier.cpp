/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file 
 * distributed with this source distribution.
 * 
 * This file is part of REDHAWK core.
 * 
 * REDHAWK core is free software: you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by the 
 * Free Software Foundation, either version 3 of the License, or (at your 
 * option) any later version.
 * 
 * REDHAWK core is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License 
 * for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License 
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

#include <ossie/MessageInterface.h>
#include <ossie/PropertyMap.h>

class MessageSupplierPort::MessageTransport : public redhawk::BasicTransport
{
public:
    MessageTransport(const std::string& connectionId, CosEventChannelAdmin::EventChannel_ptr channel) :
        redhawk::BasicTransport(connectionId, channel),
        _channel(CosEventChannelAdmin::EventChannel::_duplicate(channel))
    {
    }

    virtual ~MessageTransport()
    {
    }

    virtual void push(const CORBA::Any& data) = 0;

    virtual void beginQueue(size_t count) = 0;
    virtual void queueMessage(const std::string& msgId, const char* format, const void* msgData, MessageSupplierPort::SerializerFunc serializer) = 0;
    virtual void sendMessages() = 0;

private:
    CosEventChannelAdmin::EventChannel_var _channel;
};

class MessageSupplierPort::RemoteTransport : public MessageSupplierPort::MessageTransport
{
public:
    RemoteTransport(const std::string& connectionId, CosEventChannelAdmin::EventChannel_ptr channel) :
        MessageTransport(connectionId, channel)
    {
        CosEventChannelAdmin::SupplierAdmin_var supplier_admin = channel->for_suppliers();
        _consumer = supplier_admin->obtain_push_consumer();
        _consumer->connect_push_supplier(CosEventComm::PushSupplier::_nil());
    }

    void push(const CORBA::Any& data)
    {
        _consumer->push(data);
    }

    void beginQueue(size_t count)
    {
        // Pre-allocate enough space to hold the entire queue
        if (_queue.maximum() < count) {
            _queue.replace(count, 0, CF::Properties::allocbuf(count), true);
        } else {
            _queue.length(0);
        }
    }

    void queueMessage(const std::string& msgId, const char* /*unused*/, const void* msgData, MessageSupplierPort::SerializerFunc serializer)
    {
        CORBA::ULong index = _queue.length();
        _queue.length(index+1);
        CF::DataType& message = _queue[index];
        message.id = msgId.c_str();
        serializer(message.value, msgData);
    }

    void sendMessages()
    {
        CORBA::Any data;
        data <<= _queue;
        push(data);
    }

    void disconnect()
    {
        try {
            _consumer->disconnect_push_consumer();
        } catch (...) {
            // Ignore errors on disconnect
        }
    }

private:
    CosEventChannelAdmin::ProxyPushConsumer_var _consumer;
    CF::Properties _queue;
};

class MessageSupplierPort::LocalTransport : public MessageSupplierPort::MessageTransport
{
public:
    LocalTransport(const std::string& connectionId, MessageConsumerPort* consumer,
                   CosEventChannelAdmin::EventChannel_ptr channel) :
        MessageTransport(connectionId, channel),
        _consumer(consumer)
    {
    }

    void push(const CORBA::Any& data)
    {
        CF::Properties* temp;
        if (!(data >>= temp)) {
            return;
        }
        const redhawk::PropertyMap& props = redhawk::PropertyMap::cast(*temp);
        for (redhawk::PropertyMap::const_iterator msg = props.begin(); msg != props.end(); ++msg) {
            _consumer->fireCallback(msg->getId(), msg->getValue());
        }
    }

    void beginQueue(size_t /*unused*/)
    {
    }

    void queueMessage(const std::string& msgId, const char* format, const void* msgData, MessageSupplierPort::SerializerFunc serializer)
    {
        CallbackEntry* entry = getCallback(msgId, format);
        if (entry) {
            // There is a message-specific callback registered; use direct
            // dispatch if available, otherwise fall back to CORBA Any
            if (entry->direct) {
                entry->callback->dispatch(msgId, msgData); 
            } else {
                CORBA::Any data;
                serializer(data, msgData);
                entry->callback->dispatch(msgId, data);
            }
        }

        // If the receiver has any generic callbacks registered, serialize the
        // message to a CORBA Any (which, technically speaking, may have also
        // been done above if the message format differed) and send it along.
        // By serializing only when it's required, the best case of direct
        // message dispatch runs significantly faster.
        if (_consumer->hasGenericCallbacks()) {
            CORBA::Any data;
            serializer(data, msgData);
            _consumer->dispatchGeneric(msgId, data);
        }
    }

    void sendMessages()
    {
    }

private:
    struct CallbackEntry {
        MessageConsumerPort::MessageCallback* callback;
        bool direct;
    };

    typedef std::map<std::string,CallbackEntry> CallbackTable;

    CallbackEntry* getCallback(const std::string& msgId, const char* format)
    {
        CallbackTable::iterator callback = _callbacks.find(msgId);
        if (callback != _callbacks.end()) {
            // The callback has already been found and negotiated
            return &(callback->second);
        }

        // No callback has been found yet; ask the consumer for its callback,
        // and if it has one, negotiate whether we can use direct dispatch via
        // void*
        CallbackEntry entry;
        entry.callback = _consumer->getMessageCallback(msgId);
        if (entry.callback) {
            entry.direct = entry.callback->isCompatible(format);
            callback = _callbacks.insert(std::make_pair(msgId, entry)).first;
            return &(callback->second);
        }

        // There is no callback registered for the given message
        return 0;
    }

    MessageConsumerPort* _consumer;
    CallbackTable _callbacks;
};

MessageSupplierPort::MessageSupplierPort (const std::string& name) :
    UsesPort(name)
{
}

MessageSupplierPort::~MessageSupplierPort (void)
{
}

void MessageSupplierPort::_validatePort(CORBA::Object_ptr object)
{
    const std::string rep_id(CosEventChannelAdmin::EventChannel::_PD_repoId);
    bool valid;
    try {
        valid = object->_is_a(rep_id.c_str());
    } catch (...) {
        // If _is_a throws an exception, assume the remote object is
        // unreachable (e.g., dead)
        throw CF::Port::InvalidPort(1, "Object unreachable");
    }

    if (!valid) {
        std::string message = "Object does not support " + rep_id;
        throw CF::Port::InvalidPort(1, message.c_str());
    }
}

redhawk::BasicTransport* MessageSupplierPort::_createTransport(CORBA::Object_ptr object, const std::string& connectionId)
{
    CosEventChannelAdmin::EventChannel_var channel = ossie::corba::_narrowSafe<CosEventChannelAdmin::EventChannel>(object);
    if (CORBA::is_nil(channel)) {
        throw CF::Port::InvalidPort(0, "The object provided did not narrow to a CosEventChannelAdmin::EventChannel type");
    }

    MessageConsumerPort* local_port = ossie::corba::getLocalServant<MessageConsumerPort>(channel);
    if (local_port) {
        return new LocalTransport(connectionId, local_port, channel);
    } else {
        return new RemoteTransport(connectionId, channel);
    }
}

void MessageSupplierPort::push(const CORBA::Any& data)
{
    boost::mutex::scoped_lock lock(updatingPortsLock);
    for (TransportList::iterator iter = _transports.begin(); iter != _transports.end(); ++iter) {
        MessageTransport* transport = static_cast<MessageTransport*>(*iter);
        try {
            transport->push(data);
        } catch ( ... ) {
        }
    }
}

std::string MessageSupplierPort::getRepid() const 
{
    return ExtendedEvent::MessageEvent::_PD_repoId;
}

void MessageSupplierPort::_beginMessageQueue(size_t count)
{
    for (TransportList::iterator iter = _transports.begin(); iter != _transports.end(); ++iter) {
        MessageTransport* transport = static_cast<MessageTransport*>(*iter);
        transport->beginQueue(count);
    }
}

void MessageSupplierPort::_queueMessage(const std::string& msgId, const char* format, const void* msgData, SerializerFunc serializer)
{
    for (TransportList::iterator iter = _transports.begin(); iter != _transports.end(); ++iter) {
        MessageTransport* transport = static_cast<MessageTransport*>(*iter);
        try {
            transport->queueMessage(msgId, format, msgData, serializer);
        } catch ( ... ) {
        }
    }
}

void MessageSupplierPort::_sendMessageQueue()
{
    for (TransportList::iterator iter = _transports.begin(); iter != _transports.end(); ++iter) {
        MessageTransport* transport = static_cast<MessageTransport*>(*iter);
        transport->sendMessages();
    }
}
