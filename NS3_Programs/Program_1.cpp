// PROJECT 1: Basic UDP Echo Communication
// Purpose: A UDP client sends packets to an echo server, which sends them back.

#include "ns3/core-module.h"       // Simulation time, events, logging
#include "ns3/network-module.h"    // Nodes, packets, network devices
#include "ns3/internet-module.h"   // IP networking stack and addressing
#include "ns3/point-to-point-module.h" // Point-to-point links
#include "ns3/applications-module.h"   // UDP echo client and server

using namespace ns3;

int main(int argc, char *argv[])
{
    // Create two nodes: Node 0 is the client; Node 1 is the server.
    NodeContainer nodes;
    nodes.Create(2);

    // Configure the link speed and propagation delay.
    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));

    // Connect the two nodes with the configured point-to-point link.
    NetDeviceContainer devices = pointToPoint.Install(nodes);

    // Install the Internet protocol stack on both nodes.
    InternetStackHelper internet;
    internet.Install(nodes);

    // Assign IPv4 addresses to the two ends of the link.
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = address.Assign(devices);
    // The assigned addresses are normally 10.1.1.1 and 10.1.1.2.

    // Configure a UDP echo server on Node 1, listening on port 9.
    uint16_t port = 9;
    UdpEchoServerHelper server(port);
    ApplicationContainer serverApp = server.Install(nodes.Get(1));
    serverApp.Start(Seconds(1.0));  // Start the server at simulation time 1 s.
    serverApp.Stop(Seconds(10.0));  // Stop the server at simulation time 10 s.

    // Configure the UDP echo client on Node 0, targeting Node 1's IP address.
    UdpEchoClientHelper client(interfaces.GetAddress(1), port);
    client.SetAttribute("MaxPackets", UintegerValue(10)); // Send at most 10 packets.
    client.SetAttribute("Interval", TimeValue(Seconds(1.0))); // 1 s between packets.
    client.SetAttribute("PacketSize", UintegerValue(1024)); // Each packet is 1024 bytes.

    // Install the client and define when it runs.
    ApplicationContainer clientApp = client.Install(nodes.Get(0));
    clientApp.Start(Seconds(2.0)); // Start sending at 2 s.
    clientApp.Stop(Seconds(9.0));  // Stop the client at 9 s.

    // Enable PCAP packet capture for the point-to-point devices.
    // The generated capture files can be opened with Wireshark.
    pointToPoint.EnablePcapAll("udp-two-node");

    // Run the discrete-event simulation until 10 seconds.
    Simulator::Stop(Seconds(10.0));
    Simulator::Run();

    // Release simulation resources.
    Simulator::Destroy();
    return 0;
}
