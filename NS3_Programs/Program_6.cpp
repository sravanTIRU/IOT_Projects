// PROJECT 6: UDP Congestion and Throughput
// Purpose: Send UDP traffic faster than the link can carry and measure received throughput.
// Note: This version does not calculate an exact packet-loss count.

#include "ns3/core-module.h"           // Simulation utilities
#include "ns3/network-module.h"        // Nodes and devices
#include "ns3/internet-module.h"       // IP stack and addressing
#include "ns3/point-to-point-module.h" // Point-to-point link and queue
#include "ns3/applications-module.h"   // UDP source and PacketSink

using namespace ns3;

int main(int argc, char *argv[])
{
    // Create sender and receiver nodes.
    NodeContainer nodes;
    nodes.Create(2);

    // Configure a 1 Mbps link with 10 ms propagation delay.
    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("1Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("10ms"));

    // Limit the device queue to 10 packets. DropTail drops new packets if full.
    p2p.SetQueue("ns3::DropTailQueue",
                 "MaxSize", StringValue("10p"));

    // Connect nodes and install IP networking.
    NetDeviceContainer devices = p2p.Install(nodes);
    InternetStackHelper internet;
    internet.Install(nodes);

    // Assign IPv4 addresses to the link.
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = address.Assign(devices);

    // Set up a UDP receiver on Node 1 at port 9000.
    uint16_t port = 9000;
    PacketSinkHelper sink(
        "ns3::UdpSocketFactory",
        InetSocketAddress(Ipv4Address::GetAny(), port));
    ApplicationContainer server = sink.Install(nodes.Get(1));
    server.Start(Seconds(1.0));
    server.Stop(Seconds(10.0));

    // Generate traffic at 2 Mbps, faster than the 1 Mbps link can transmit.
    // This can fill the queue and cause packet drops.
    OnOffHelper source(
        "ns3::UdpSocketFactory",
        InetSocketAddress(interfaces.GetAddress(1), port));
    source.SetAttribute("DataRate", StringValue("2Mbps"));
    source.SetAttribute("PacketSize", UintegerValue(1024));
    source.SetAttribute("OnTime", StringValue(
        "ns3::ConstantRandomVariable[Constant=1]"));
    source.SetAttribute("OffTime", StringValue(
        "ns3::ConstantRandomVariable[Constant=0]"));

    ApplicationContainer client = source.Install(nodes.Get(0));
    client.Start(Seconds(2.0));
    client.Stop(Seconds(9.0));

    // Run the simulation until 10 seconds.
    Simulator::Stop(Seconds(10.0));
    Simulator::Run();

    // Retrieve the receiver and read total bytes received.
    Ptr<PacketSink> receiver = DynamicCast<PacketSink>(server.Get(0));
    uint64_t receivedBytes = receiver->GetTotalRx();

    // The sender runs from 2 s to 9 s, so this example uses a 7-second interval.
    // This is an approximate application-interval throughput calculation.
    double duration = 7.0;
    double throughput = (receivedBytes * 8.0) / (duration * 1000.0);

    std::cout << "=== PACKET LOSS AND THROUGHPUT ===" << std::endl;
    std::cout << "Bytes received: " << receivedBytes << std::endl;
    std::cout << "Throughput: " << throughput << " Kbps" << std::endl;

    // Exact packet loss is not measured here; it requires transmitted and
    // received packet counts for the same flow and measurement interval.
    std::cout << "Note: Exact packet loss requires counting transmitted "
              << "and received packets." << std::endl;

    // Clean up.
    Simulator::Destroy();
    return 0;
}
