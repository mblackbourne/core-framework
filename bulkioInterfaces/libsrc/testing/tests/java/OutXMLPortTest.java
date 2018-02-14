/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file
 * distributed with this source distribution.
 *
 * This file is part of REDHAWK bulkioInterfaces.
 *
 * REDHAWK bulkioInterfaces is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * REDHAWK bulkioInterfaces is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

import org.junit.*;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

import stubs.Packet;

@RunWith(JUnit4.class)
public class OutXMLPortTest extends impl.OutXMLPortTestImpl
{
    public OutXMLPortTest()
    {
    }

    @Test
    public void testPushPacketData()
    {
        BULKIO.StreamSRI sri = bulkio.sri.utils.create("push_packet");
        port.pushSRI(sri);

        String document = "<document><body attribute=\"value\"/></document>";

        // Check the received data is consistent
        port.pushPacket(document, false, sri.streamID);
        Assert.assertEquals(1, stub.packets.size());
        Packet<String> packet = stub.packets.get(0);
        Assert.assertEquals(document, packet.data);
    }
}
