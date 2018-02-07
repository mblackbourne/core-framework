#!/usr/bin/python
#
# This file is protected by Copyright. Please refer to the COPYRIGHT file
# distributed with this source distribution.
#
# This file is part of REDHAWK bulkioInterfaces.
#
# REDHAWK bulkioInterfaces is free software: you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any
# later version.
#
# REDHAWK bulkioInterfaces is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
# details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see http://www.gnu.org/licenses/.
#

import unittest
import math

import bulkio
from bulkio.bulkioInterfaces import BULKIO

from helpers import *

class OutStreamTest(object):
    def setUp(self):
        self.port = self.helper.createOutPort()
        self.stub = self._createStub()

        objref = self.stub._this()
        self.port.connectPort(objref, 'test_connection')

    def tearDown(self):
        try:
            self._disconnectPorts()
        except:
            # Ignore disconnection errors
            pass

        self._releaseServants()

    def _createStub(self):
        return self.helper.createInStub()

    def _disconnectPorts(self):
        for connection in self.port._get_connections():
            self.port.disconnectPort(connection.connectionId)

    def _releaseServants(self):
        poa = self.stub._default_POA()
        object_id = poa.servant_to_id(self.stub)
        poa.deactivate_object(object_id)

    def testBasicWrite(self):
        stream = self.port.createStream('test_basic_write')
        self.failUnless(not self.stub.packets)

        time = bulkio.timestamp.now()
        self._writeSinglePacket(stream, 256, time)
        self.assertEqual(1, len(self.stub.packets))
        self.assertEqual(256, self.helper.dataLength(self.stub.packets[0].data))
        self.failIf(self.stub.packets[0].EOS)
        self.assertEqual(stream.streamID, self.stub.packets[0].streamID)

        # Check timestamp, but only if it's supported (i.e., not dataXML)
        if hasattr(self.stub.Packet, 'T'):
            self.assertEqual(time, self.stub.packets[0].T, msg='Received incorrect time stamp')

    def testSriFields(self):
        sri = bulkio.sri.create("test_sri")
        sri.xstart = -2.5
        sri.xdelta = 0.125
        sri.xunits = BULKIO.UNITS_FREQUENCY
        sri.subsize = 1024
        sri.ystart = 2.5
        sri.ydelta = 1.0
        sri.yunits = BULKIO.UNITS_TIME
        sri.mode = 1
        sri.blocking = 1
        # TODO: keywords

        # Create a stream from the SRI and compare accessors
        stream = self.port.createStream(sri)
        self.assertEqual(stream.streamID, sri.streamID)
        self.assertEqual(stream.xstart, sri.xstart)
        self.assertEqual(stream.xdelta, sri.xdelta)
        self.assertEqual(stream.xunits, sri.xunits)
        self.assertEqual(stream.subsize, sri.subsize)
        self.assertEqual(stream.ystart, sri.ystart)
        self.assertEqual(stream.ydelta, sri.ydelta)
        self.assertEqual(stream.yunits, sri.yunits)
        self.failUnless(stream.complex)
        self.failUnless(stream.blocking)
        # TODO: keywords

    def testSriUpdate(self):
        # Create initial stream; all changes should be queued up for the first
        # write
        stream = self.port.createStream("test_sri_update")
        xdelta = 1.0 / 1.25e6
        stream.xdelta = xdelta
        stream.blocking = True
        self.failUnless(not self.stub.H)

        # Write data to trigger initial SRI update
        self._writeSinglePacket(stream, 10)
        self.assertEqual(len(self.stub.H), 1)
        self.failUnless(self.stub.H[-1].blocking)
        self.assertEqual(xdelta, self.stub.H[-1].xdelta)

        # Update xdelta; no SRI update should occur
        new_xdelta = 1.0/2.5e6
        stream.xdelta = new_xdelta
        self.assertEqual(len(self.stub.H), 1)
        self.assertEqual(xdelta, self.stub.H[-1].xdelta)

        # Write data to trigger SRI update
        self._writeSinglePacket(stream, 25)
        self.assertEqual(len(self.stub.H), 2)
        self.assertEqual(new_xdelta, self.stub.H[-1].xdelta)

        # Change blocking flag, then trigger an SRI update
        stream.blocking = False
        self.assertEqual(len(self.stub.H), 2)
        self.failUnless(self.stub.H[-1].blocking)
        self._writeSinglePacket(stream, 25)
        self.assertEqual(len(self.stub.H), 3)
        self.failIf(self.stub.H[-1].blocking)

        # Change multiple fields, but only one SRI update should occur (after the
        # next write)
        stream.complex = True
        stream.subsize = 16
        stream.xstart = -math.pi
        stream.xdelta = 2.0 * math.pi / 1024.0
        stream.xunits = BULKIO.UNITS_FREQUENCY
        stream.ydelta = 1024.0 / 1.25e6
        stream.yunits = BULKIO.UNITS_TIME
        self.assertEqual(len(self.stub.H), 3)

        # Trigger SRI update and verify that it matches
        self._writeSinglePacket(stream, 1024)
        self.assertEqual(len(self.stub.H), 4)
        self.failUnless(bulkio.sri.compare(stream.sri(), self.stub.H[-1]))

    def testKeywords(self):
        # TODO
        pass

    def testSendEosOnClose(self):
        stream = self.port.createStream("close_eos")

        self.assertEqual(len(self.stub.H), 0)
        self.assertEqual(len(self.stub.packets), 0)

        self._writeSinglePacket(stream, 16)

        self.assertEqual(len(self.stub.H), 1)
        self.assertEqual(len(self.stub.packets), 1)
        self.failIf(self.stub.packets[-1].EOS)

        stream.close()
        self.assertEqual(len(self.stub.packets), 2)
        self.failUnless(self.stub.packets[-1].EOS)

    def _writeSinglePacket(self, stream, length, time=None):
        if time is None:
            time = bulkio.timestamp.now()
        data = self.helper.createData(length)
        stream.write(data, time)

def register_test(name, testbase, **kwargs):
    globals()[name] = type(name, (testbase, unittest.TestCase), kwargs)

register_test('OutBitStreamTest', OutStreamTest, helper=BitTestHelper())
register_test('OutXMLStreamTest', OutStreamTest, helper=XMLTestHelper())
register_test('OutFileStreamTest', OutStreamTest, helper=FileTestHelper())
register_test('OutCharStreamTest', OutStreamTest, helper=CharTestHelper())
register_test('OutOctetStreamTest', OutStreamTest, helper=OctetTestHelper())
register_test('OutShortStreamTest', OutStreamTest, helper=ShortTestHelper())
register_test('OutUShortStreamTest', OutStreamTest, helper=UShortTestHelper())
register_test('OutLongStreamTest', OutStreamTest, helper=LongTestHelper())
register_test('OutULongStreamTest', OutStreamTest, helper=ULongTestHelper())
register_test('OutLongLongStreamTest', OutStreamTest, helper=LongLongTestHelper())
register_test('OutULongLongStreamTest', OutStreamTest, helper=ULongLongTestHelper())
register_test('OutFloatStreamTest', OutStreamTest, helper=FloatTestHelper())
register_test('OutDoubleStreamTest', OutStreamTest, helper=DoubleTestHelper())

if __name__ == '__main__':
    from ossie.utils.log4py import logging
    logging.basicConfig()
    logging.getLogger().setLevel(logging.TRACE)

    from omniORB import CORBA
    orb = CORBA.ORB_init()
    root_poa = orb.resolve_initial_references("RootPOA")
    manager = root_poa._get_the_POAManager()
    manager.activate()

    unittest.main()

    orb.shutdown(True)
