#!/usr/bin/python3

import sys

from scapy.all import RandMAC, RandIP, PcapWriter, RandIP6, RandShort, fuzz
from scapy.all import IPv6, Dot1Q, IP, Ether, UDP, TCP

if len(sys.argv) == 1 or sys.argv[1] != 'fuzz':
    while True:
        eth = Ether(dst='ff:ff:ff:ff:ff:ff')
        vlan = eth/Dot1Q(vlan=1)
        p = eth/IP()/TCP(sport=20,dport=80,flags='SA',window=8192)
        print(p.build().hex())
        p = eth/IP()/UDP(sport=53,dport=53)
        print(p.build().hex())
        p = eth/IP()/TCP(sport=20,dport=80,flags='S',window=8192)
        print(p.build().hex())
        p = eth/IP()/UDP(sport=53,dport=53)
        print(p.build().hex())
        p = vlan/IP()/UDP(sport=53,dport=53)
        print(p.build().hex())
        p = vlan/IP()/TCP(sport=20,dport=80,flags='S',window=8192)
        print(p.build().hex())
else:
    while True:
        # Generate random protocol bases, use a fuzz() over the combined packet
        # for full fuzzing.
        eth = Ether(src=RandMAC(), dst=RandMAC())
        vlan = Dot1Q()
        ipv4 = IP(src=RandIP(), dst=RandIP())
        ipv6 = IPv6(src=RandIP6(), dst=RandIP6())
        udp = UDP(dport=RandShort(), sport=RandShort())
        tcp = TCP(dport=RandShort(), sport=RandShort())

        # IPv4 packets with fuzzing
        print(fuzz(eth / ipv4 / udp).build().hex())
        print(fuzz(eth / ipv4 / tcp).build().hex())
        print(fuzz(eth / vlan / ipv4 / udp).build().hex())
        print(fuzz(eth / vlan / ipv4 / tcp).build().hex())

        # IPv6 packets with fuzzing
        print(fuzz(eth / ipv6 / udp).build().hex())
        print(fuzz(eth / ipv6 / tcp).build().hex())
        print(fuzz(eth / vlan / ipv6 / udp).build().hex())
        print(fuzz(eth / vlan / ipv6 / tcp).build().hex())

