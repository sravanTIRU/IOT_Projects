// PROJECT 5: TCP and UDP Communication Comparison
// Purpose: Run TCP and UDP traffic between the same two nodes and compare received bytes.

#include "ns3/core-module.h"           // Simulation utilities
#include "ns3/network-module.h"        // Nodes and devices
#include "ns3/internet-module.h"       // IP stack and addressing
#include "ns3/point-to-point-module.h" // Point-to-point link
#include "ns3/applications-module.h"   // BulkSend and PacketSink applications

using namespace ns3;

int main(int argc, char *argv[])
{
    // Create two nodes: sender (0) and receiver (1).
    NodeContainer nodes;
    nodes.Create(2);

    // Configure the link.
    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));
    NetDeviceContainer devices = p2p.Install(nodes);

    // Install IP networking and assign addresses.
    InternetStackHelper internet;
    internet.Install(nodes);
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = address.Assign(devices);

    // Use different destination ports so TCP and UDP traffic are separated.
    uint16_t tcpPort = 5000;
    uint16_t udpPort = 6000;

    // TCP receiver: listens on port 5000.
    PacketSinkHelper tcpSink(
        "ns3::TcpSocketFactory",
        InetSocketAddress(Ipv4Address::GetAny(), tcpPort));
    ApplicationContainer tcpServer = tcpSink.Install(nodes.Get(1));
    tcpServer.Start(Seconds(1.0));
    tcpServer.Stop(Seconds(10.0));

    // TCP sender: sends up to 50,000 bytes using reliable TCP.
    BulkSendHelper tcpClient(
        "ns3::TcpSocketFactory",
        InetSocketAddress(interfaces.GetAddress(1), tcpPort));
    tcpClient.SetAttribute("MaxBytes", UintegerValue(50000));
    ApplicationContainer tcpApp = tcpClient.Install(nodes.Get(0));
    tcpApp.Start(Seconds(2.0));
    tcpApp.Stop(Seconds(9.0));

    // UDP receiver: listens on port 6000.
    PacketSinkHelper udpSink(
        "ns3::UdpSocketFactory",
        InetSocketAddress(Ipv4Address::GetAny(), udpPort));
    ApplicationContainer udpServer = udpSink.Install(nodes.Get(1));
    udpServer.Start(Seconds(1.0));
    udpServer.Stop(Seconds(10.0));

    // UDP sender: generates 512-byte packets at a configured rate of 500 Kbps.
    OnOffHelper udpClient(
        "ns3::UdpSocketFactory",
        InetSocketAddress(interfaces.GetAddress(1), udpPort));
    udpClient.SetAttribute("DataRate", StringValue("500Kbps"));
    udpClient.SetAttribute("PacketSize", UintegerValue(512));
    udpClient.SetAttribute("OnTime", StringValue(
        "ns3::ConstantRandomVariable[Constant=1]"));
    udpClient.SetAttribute("OffTime", StringValue(
        "ns3::ConstantRandomVariable[Constant=0]"));

    ApplicationContainer udpApp = udpClient.Install(nodes.Get(0));
    udpApp.Start(Seconds(2.0));
    udpApp.Stop(Seconds(9.0));

    // Run the simulation.
    Simulator::Stop(Seconds(10.0));
    Simulator::Run();

    // Retrieve the PacketSink applications so their received byte totals can be read.
    Ptr<PacketSink> tcp = DynamicCast<PacketSink>(tcpServer.Get(0));
    Ptr<PacketSink> udp = DynamicCast<PacketSink>(udpServer.Get(0));

    // Print received application payload bytes for each protocol.
    std::cout << "\n=== TCP AND UDP COMMUNICATION ===\n";
    std::cout << "TCP Bytes Received: " << tcp->GetTotalRx() << std::endl;
    std::cout << "UDP Bytes Received: " << udp->GetTotalRx() << std::endl;

    // Clean up.
    Simulator::Destroy();
    return 0;
}
