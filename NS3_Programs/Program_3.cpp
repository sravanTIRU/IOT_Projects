// PROJECT 3: Three-Node Network with Routing
// Purpose: Send UDP packets from a source through a router to a destination.

#include "ns3/core-module.h"           // Simulation utilities
#include "ns3/network-module.h"        // Nodes and devices
#include "ns3/internet-module.h"       // IP stack and routing
#include "ns3/point-to-point-module.h" // Point-to-point links
#include "ns3/applications-module.h"   // UDP client and server

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("ThreeNodeNetwork");

int main(int argc, char *argv[])
{
    // Create three nodes: source (0), router (1), and destination (2).
    NodeContainer nodes;
    nodes.Create(3);

    // Configure links with 5 Mbps capacity and 2 ms propagation delay.
    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));

    // Link 1 connects source to router; Link 2 connects router to destination.
    NetDeviceContainer d1 = p2p.Install(nodes.Get(0), nodes.Get(1));
    NetDeviceContainer d2 = p2p.Install(nodes.Get(1), nodes.Get(2));

    // Install IP networking on all three nodes.
    InternetStackHelper internet;
    internet.Install(nodes);

    // Assign a different subnet to each link.
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer i1 = address.Assign(d1);

    address.SetBase("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer i2 = address.Assign(d2);

    // Populate global IPv4 routing tables so the router can forward packets.
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // Install a UDP server on the destination node, port 9.
    uint16_t port = 9;
    UdpServerHelper server(port);
    ApplicationContainer serverApp = server.Install(nodes.Get(2));
    serverApp.Start(Seconds(1.0));
    serverApp.Stop(Seconds(10.0));

    // Configure the source to send up to five 1024-byte UDP packets to the destination.
    UdpClientHelper client(i2.GetAddress(1), port);
    client.SetAttribute("MaxPackets", UintegerValue(5));
    client.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    client.SetAttribute("PacketSize", UintegerValue(1024));

    ApplicationContainer clientApp = client.Install(nodes.Get(0));
    clientApp.Start(Seconds(2.0));
    clientApp.Stop(Seconds(9.0));

    // Capture packets on the point-to-point links for Wireshark analysis.
    p2p.EnablePcapAll("three-node-network");

    // Run the simulation.
    Simulator::Stop(Seconds(10.0));
    Simulator::Run();

    // Get the UDP server object to read how many packets it received.
    Ptr<UdpServer> udpServer = DynamicCast<UdpServer>(serverApp.Get(0));

    // Display interface addresses and the received packet count.
    std::cout << "\n=== THREE-NODE NETWORK COMMUNICATION ===\n";
    std::cout << "Source Node IP: " << i1.GetAddress(0) << "\n";
    std::cout << "Router incoming IP: " << i1.GetAddress(1) << "\n";
    std::cout << "Router outgoing IP: " << i2.GetAddress(0) << "\n";
    std::cout << "Destination Node IP: " << i2.GetAddress(1) << "\n";
    std::cout << "Packets received: " << udpServer->GetReceived() << "\n";

    // Clean up.
    Simulator::Destroy();
    return 0;
}
