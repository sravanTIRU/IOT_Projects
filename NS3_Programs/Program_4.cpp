// PROJECT 4: IoT Gateway Communication
// Purpose: Four simulated IoT nodes send UDP packets to one central gateway.

#include "ns3/core-module.h"           // Simulation utilities
#include "ns3/network-module.h"        // Nodes and network devices
#include "ns3/internet-module.h"       // IP stack and routing
#include "ns3/point-to-point-module.h" // Point-to-point links
#include "ns3/applications-module.h"   // UDP client and server

#include <string> // std::to_string used to build subnet addresses

using namespace ns3;

int main(int argc, char *argv[])
{
    // Create five nodes: four IoT devices (0-3) and gateway (4).
    NodeContainer nodes;
    nodes.Create(5);

    // Configure each IoT-to-gateway link.
    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));

    // Install the Internet stack on every node.
    InternetStackHelper internet;
    internet.Install(nodes);

    // Create one separate point-to-point link and subnet for each IoT node.
    Ipv4AddressHelper address;
    for (uint32_t i = 0; i < 4; i++)
    {
        NetDeviceContainer link = p2p.Install(nodes.Get(i), nodes.Get(4));

        // Subnets created: 10.1.1.0/24 through 10.1.4.0/24.
        // The IoT node is normally .1 and its gateway interface is .2.
        std::string subnet = "10.1." + std::to_string(i + 1) + ".0";
        address.SetBase(subnet.c_str(), "255.255.255.0");
        address.Assign(link);
    }

    // Build routes between the connected subnets.
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // The gateway receives UDP packets on port 9.
    uint16_t port = 9;
    UdpServerHelper server(port);
    ApplicationContainer serverApp = server.Install(nodes.Get(4));
    serverApp.Start(Seconds(1.0));
    serverApp.Stop(Seconds(10.0));

    // Install one UDP client on each IoT node.
    for (uint32_t i = 0; i < 4; i++)
    {
        // Each client's gateway IP is .2 in that node's own subnet.
        std::string gatewayIp =
            "10.1." + std::to_string(i + 1) + ".2";
        UdpClientHelper client(Ipv4Address(gatewayIp.c_str()), port);

        client.SetAttribute("MaxPackets", UintegerValue(5));
        client.SetAttribute("Interval", TimeValue(Seconds(1.0)));
        client.SetAttribute("PacketSize", UintegerValue(512));

        ApplicationContainer clientApp = client.Install(nodes.Get(i));

        // Stagger start times: 2.0, 2.2, 2.4, and 2.6 seconds.
        clientApp.Start(Seconds(2.0 + i * 0.2));
        clientApp.Stop(Seconds(9.0));
    }

    // Run the simulation for 10 seconds.
    Simulator::Stop(Seconds(10.0));
    Simulator::Run();

    // Read the number of UDP packets received by the gateway server.
    Ptr<UdpServer> udpServer =
        DynamicCast<UdpServer>(serverApp.Get(0));

    std::cout << "=== IoT Gateway Communication ===" << std::endl;
    std::cout << "IoT Nodes: 4" << std::endl;
    std::cout << "Gateway: Node 4" << std::endl;
    std::cout << "Packets received: " << udpServer->GetReceived()
              << std::endl;

    // Clean up the simulation.
    Simulator::Destroy();
    return 0;
}
