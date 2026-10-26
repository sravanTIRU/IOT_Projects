    Simulator::Run();

    // Ask FlowMonitor to identify packets it considers lost.
    monitor->CheckForLostPackets();

    // Obtain the classifier so each flow can be identified by its IP/port tuple.
    Ptr<Ipv4FlowClassifier> classifier =
        DynamicCast<Ipv4FlowClassifier>(flowHelper.GetClassifier());

    // Print the statistics collected for each monitored flow.
    for (const auto& flow : monitor->GetFlowStats())
    {
        Ipv4FlowClassifier::FiveTuple tuple = classifier->FindFlow(flow.first);
        const FlowMonitor::FlowStats& stats = flow.second;

        std::cout << "\nFlow: " << tuple.sourceAddress
                  << " -> " << tuple.destinationAddress << "\n";
        std::cout << "Transmitted packets: " << stats.txPackets << "\n";
        std::cout << "Received packets: " << stats.rxPackets << "\n";

        // Calculate average one-way delay only if at least one packet arrived.
        if (stats.rxPackets > 0)
        {
            double delay = stats.delaySum.GetSeconds() / stats.rxPackets;
            std::cout << "Average delay: " << delay * 1000.0 << " ms\n";

            // Estimate throughput using received bytes and the flow's observed span.
            double duration =
                (stats.timeLastRxPacket - stats.timeFirstTxPacket).GetSeconds();

            if (duration > 0)
            {
                double throughput =
                    stats.rxBytes * 8.0 / duration / 1000000.0;
                std::cout << "Throughput: " << throughput << " Mbps\n";
            }
        }
    }

    // Save FlowMonitor data to an XML file for later inspection.
    monitor->SerializeToXmlFile("bandwidth-delay.xml", true, true);

    // Clean up the simulation.
    Simulator::Destroy();
    return 0;
}
