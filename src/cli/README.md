# OpenThread CLI Reference

The OpenThread CLI exposes configuration and management APIs via a
command line interface. Use the CLI to play with OpenThread, which
can also be used with additional application code. The
OpenThread test scripts use the CLI to execute test cases.

## OpenThread Command List

* [bufferinfo](#bufferinfo)
* [channel](#channel)
* [child](#child-list)
* [childip](#childip)
* [childmax](#childmax)
* [childtimeout](#childtimeout)
* [coap](README_COAP.md)
* [coaps](README_COAPS.md)
* [commissioner](README_COMMISSIONER.md)
* [contextreusedelay](#contextreusedelay)
* [counters](#counters)
* [dataset](README_DATASET.md)
* [delaytimermin](#delaytimermin)
* [diag](#diag)
* [discover](#discover-channel)
* [dns](#dns-resolve-hostname-dns-server-ip-dns-server-port)
* [eidcache](#eidcache)
* [eui64](#eui64)
* [extaddr](#extaddr)
* [extpanid](#extpanid)
* [factoryreset](#factoryreset)
* [ifconfig](#ifconfig)
* [ipaddr](#ipaddr)
* [ipmaddr](#ipmaddr)
* [joiner](README_JOINER.md)
* [joinerport](#joinerport-port)
* [keysequence](#keysequence-counter)
* [leaderdata](#leaderdata)
* [leaderpartitionid](#leaderpartitionid)
* [leaderweight](#leaderweight)
* [linkquality](#linkquality-extaddr)
* [logfilename](#logfilename-filename)
* [mac](#mac-retries-direct)
* [macfilter](#macfilter)
* [masterkey](#masterkey)
* [mode](#mode)
* [neighbor](#neighbor-list)
* [netdataregister](#netdataregister)
* [netdatashow](#netdatashow)
* [networkdiagnostic](#networkdiagnostic-get-addr-type-)
* [networkidtimeout](#networkidtimeout)
* [networkname](#networkname)
* [networktime](#networktime)
* [panid](#panid)
* [parent](#parent)
* [parentpriority](#parentpriority)
* [ping](#ping-ipaddr-size-count-interval)
* [pollperiod](#pollperiod-pollperiod)
* [prefix](#prefix-add-prefix-pvdcsr-prf)
* [promiscuous](#promiscuous)
* [releaserouterid](#releaserouterid-routerid)
* [reset](#reset)
* [rloc16](#rloc16)
* [route](#route-add-prefix-s-prf)
* [router](#router-list)
* [routerdowngradethreshold](#routerdowngradethreshold)
* [routereligible](#routereligible)
* [routerselectionjitter](#routerselectionjitter)
* [routerupgradethreshold](#routerupgradethreshold)
* [scan](#scan-channel)
* [service](#service)
* [singleton](#singleton)
* [sntp](#sntp-query-sntp-server-ip-sntp-server-port)
* [state](#state)
* [thread](#thread-start)
* [txpower](#txpower)
* [version](#version)

## OpenThread Command Details

### bufferinfo

Show the current message buffer information.

```bash
> bufferinfo
total: 40
free: 40
6lo send: 0 0
6lo reas: 0 0
ip6: 0 0
mpl: 0 0
mle: 0 0
arp: 0 0
coap: 0 0
Done
```

### channel

Get the IEEE 802.15.4 Channel value.

```bash
> channel
11
Done
```

### channel \<channel\>

Set the IEEE 802.15.4 Channel value.

```bash
> channel 11
Done
```

### channel preferred

Get preferred channel mask.

```bash
> channel preferred
0x7fff800
Done
```

### channel supported

Get supported channel mask.

```bash
> channel supported
0x7fff800
Done
```

### child list

List attached Child IDs.

```bash
> child list
1 2 3 6 7 8
Done
```

### child table

Print table of attached children.

```bash
> child table
| ID  | RLOC16 | Timeout    | Age        | LQ In | C_VN |R|S|D|N| Extended MAC     |
+-----+--------+------------+------------+-------+------+-+-+-+-+------------------+
|   1 | 0xe001 |        240 |         44 |     3 |  237 |1|1|1|1| d28d7f875888fccb |
|   2 | 0xe002 |        240 |         27 |     3 |  237 |0|1|0|1| e2b3540590b0fd87 |
Done
```

### child \<id\>

Print diagnostic information for an attached Thread Child.  The `id` may be a Child ID or an RLOC16.

```bash
> child 1
Child ID: 1
Rloc: 9c01
Ext Addr: e2b3540590b0fd87
Mode: rsn
Net Data: 184
Timeout: 100
Age: 0
Link Quality In: 3
RSSI: -20
Done
```

### childip

Get the list of IP addresses stored for MTD children.

```bash
> childip
3401: fdde:ad00:beef:0:3037:3e03:8c5f:bc0c
Done
```

### childmax

Get the Thread maximum number of allowed children.

```bash
> childmax
5
Done
```

### childmax \<count\>

Set the Thread maximum number of allowed children.

```bash
> childmax 2
Done
```

### childtimeout

Get the Thread Child Timeout value.

```bash
> childtimeout
300
Done
```

### childtimeout \<timeout\>

Set the Thread Child Timeout value.

```bash
> childtimeout 300
Done
```

### contextreusedelay

Get the CONTEXT_ID_REUSE_DELAY value.

```bash
> contextreusedelay
11
Done
```

### contextreusedelay \<delay\>

Set the CONTEXT_ID_REUSE_DELAY value.

```bash
> contextreusedelay 11
Done
```

### counters

Get the supported counter names.

```bash
> counters
mac
mle
Done
```

### counters \<countername\>

Get the counter value.

```bash
> counters mac
TxTotal: 10
    TxUnicast: 3
    TxBroadcast: 7
    TxAckRequested: 3
    TxAcked: 3
    TxNoAckRequested: 7
    TxData: 10
    TxDataPoll: 0
    TxBeacon: 0
    TxBeaconRequest: 0
    TxOther: 0
    TxRetry: 0
    TxErrCca: 0
    TxErrBusyChannel: 0
RxTotal: 2
    RxUnicast: 1
    RxBroadcast: 1
    RxData: 2
    RxDataPoll: 0
    RxBeacon: 0
    RxBeaconRequest: 0
    RxOther: 0
    RxAddressFiltered: 0
    RxDestAddrFiltered: 0
    RxDuplicated: 0
    RxErrNoFrame: 0
    RxErrNoUnknownNeighbor: 0
    RxErrInvalidSrcAddr: 0
    RxErrSec: 0
    RxErrFcs: 0
    RxErrOther: 0
Done
> counters mle
Role Disabled: 0
Role Detached: 1
Role Child: 0
Role Router: 0
Role Leader: 1
Attach Attempts: 1
Partition Id Changes: 1
Better Partition Attach Attempts: 0
Parent Changes: 0
Done
```

### counters \<countername\> reset

Reset the counter value.

```bash
> counters mac reset
Done
> counters mle reset
Done
```

### networktime

Get the Thread network time and the time sync parameters.

```bash
> networktime
Network Time:     21084154us (synchronized)
Time Sync Period: 100s
XTAL Threshold:   300ppm
Done
```

### networktime \<timesyncperiod\> \<xtalthreshold\>

Set time sync parameters

* timesyncperiod: The time synchronization period, in seconds.
* xtalthreshold: The XTAL accuracy threshold for a device to become Router-Capable device, in PPM.

```bash
> networktime 100 300
Done
```

### delaytimermin

Get the minimal delay timer (in seconds).

```bash
> delaytimermin
30
Done
```

### delaytimermin \<delaytimermin\>

Set the minimal delay timer (in seconds).

```bash
> delaytimermin 60
Done
```

### discover \[channel\]

Perform an MLE Discovery operation.

* channel: The channel to discover on.  If no channel is provided, the discovery will cover all valid channels.

```bash
> discover
| J | Network Name     | Extended PAN     | PAN  | MAC Address      | Ch | dBm | LQI |
+---+------------------+------------------+------+------------------+----+-----+-----+
| 0 | OpenThread       | dead00beef00cafe | ffff | f1d92a82c8d8fe43 | 11 | -20 |   0 |
Done
```

### dns resolve \<hostname\> \[DNS server IP\] \[DNS server port\]

Send DNS Query to obtain IPv6 address for given hostname.
The latter two parameters have following default values:
 * DNS server IP: 2001:4860:4860::8888 (Google DNS Server)
 * DNS server port: 53

```bash
> dns resolve ipv6.google.com
> DNS response for ipv6.google.com - 2a00:1450:401b:801:0:0:0:200e TTL: 300
```

### eidcache

Print the EID-to-RLOC cache entries.

```bash
> eidcache
fdde:ad00:beef:0:bb1:ebd6:ad10:f33 ac00
fdde:ad00:beef:0:110a:e041:8399:17cd 6000
Done
```

### eui64

Get the factory-assigned IEEE EUI-64.

```bash
> eui64
0615aae900124b00
Done
```

### extaddr

Get the IEEE 802.15.4 Extended Address.

```bash
> extaddr
dead00beef00cafe
Done
```

### extaddr \<extaddr\>

Set the IEEE 802.15.4 Extended Address.

```bash
> extaddr dead00beef00cafe
dead00beef00cafe
Done
```

### extpanid

Get the Thread Extended PAN ID value.

```bash
> extpanid
dead00beef00cafe
Done
```

### extpanid \<extpanid\>

Set the Thread Extended PAN ID value.

```bash
> extpanid dead00beef00cafe
Done
```

### factoryreset
Delete all stored settings, and signal a platform reset.

```bash
> factoryreset
```

### ifconfig

Show the status of the IPv6 interface.

```bash
> ifconfig
down
Done
```

### ifconfig up

Bring up the IPv6 interface.

```bash
> ifconfig up
Done
```

### ifconfig down

Bring down the IPv6 interface.

```bash
> ifconfig down
Done
```

### ipaddr

List all IPv6 addresses assigned to the Thread interface.

```bash
> ipaddr
fdde:ad00:beef:0:0:ff:fe00:0
fdde:ad00:beef:0:558:f56b:d688:799
fe80:0:0:0:f3d9:2a82:c8d8:fe43
Done
```

### ipaddr add \<ipaddr\>

Add an IPv6 address to the Thread interface.

```bash
> ipaddr add 2001::dead:beef:cafe
Done
```

### ipaddr del \<ipaddr\>

Delete an IPv6 address from the Thread interface.

```bash
> ipaddr del 2001::dead:beef:cafe
Done
```

### ipaddr linklocal

Print Thread link-local IPv6 address.

```bash
> ipaddr linklocal
fe80:0:0:0:f3d9:2a82:c8d8:fe43
Done
```

### ipaddr mleid

Print Thread Mesh Local EID address.

```bash
> ipaddr mleid
fdde:ad00:beef:0:558:f56b:d688:799
Done
```

### ipaddr rloc

Print Thread Routing Locator (RLOC) address.

```bash
> ipaddr rloc
fdde:ad00:beef:0:0:ff:fe00:0
Done
```

### ipmaddr

List all IPv6 multicast addresses subscribed to the Thread interface.

```bash
> ipmaddr
ff05:0:0:0:0:0:0:1
ff33:40:fdde:ad00:beef:0:0:1
ff32:40:fdde:ad00:beef:0:0:1
Done
```

### ipmaddr add \<ipaddr\>

Subscribe the Thread interface to the IPv6 multicast address.

```bash
> ipmaddr add ff05::1
Done
```

### ipmaddr del \<ipaddr\>

Unsubscribe the Thread interface to the IPv6 multicast address.

```bash
> ipmaddr del ff05::1
Done
```

### ipmaddr promiscuous

Get multicast promiscuous mode.

```bash
> ipmaddr promiscuous
Disabled
Done
```

### ipmaddr promiscuous enable

Enable multicast promiscuous mode.

```bash
> ipmaddr promiscuous enable
Done
```

### ipmaddr promiscuous disable

Disable multicast promiscuous mode.

```bash
> ipmaddr promiscuous disable
Done
```

### joinerport \<port\>

Set the Joiner port.

```bash
> joinerport 1000
Done
```

### keysequence counter

Get the Thread Key Sequence Counter.

```bash
> keysequence counter
10
Done
```

### keysequence counter \<counter\>

Set the Thread Key Sequence Counter.

```bash
> keysequence counter 10
Done
```

### keysequence guardtime

Get Thread Key Switch Guard Time (in hours)

```bash
> keysequence guardtime
0
Done
```

### keysequence guardtime \<guardtime\>

Set Thread Key Switch Guard Time (in hours)
0 means Thread Key Switch imediately if key index match

```bash
> keysequence guardtime 0
Done
```

### leaderpartitionid

Get the Thread Leader Partition ID.

```bash
> leaderpartitionid
4294967295
Done
```

### leaderpartitionid \<partitionid\>

Set the Thread Leader Partition ID.

```bash
> leaderpartitionid 0xffffffff
Done
```

### leaderdata

Show the Thread Leader Data.

```bash
> leaderdata
Partition ID: 1077744240
Weighting: 64
Data Version: 109
Stable Data Version: 211
Leader Router ID: 60
Done
```

### leaderweight

Get the Thread Leader Weight.

```bash
> leaderweight
128
Done
```

### leaderweight \<weight\>

Set the Thread Leader Weight.

```bash
> leaderweight 128
Done
```

### linkquality \<extaddr\>

Get the link quality on the link to a given extended address.

```bash
> linkquality 36c1dd7a4f5201ff
3
Done
```

### linkquality \<extaddr\> \<linkquality\>

Set the link quality on the link to a given extended address.

```bash
> linkquality 36c1dd7a4f5201ff 3
Done
```

### logfilename \<filename\>

- Note: POSIX Platform Only, ie: `OPENTHREAD_EXAMPLES_POSIX`
- Requires `OPENTHREAD_CONFIG_LOG_OUTPUT == OPENTHREAD_CONFIG_LOG_OUTPUT_DEBUG_UART`

Specifies filename to capture otPlatLog() messages, useful when
debugging automated test scripts on Linux when logging disrupts
the automated test scripts.

### masterkey

Get the Thread Master Key value.

```bash
> masterkey
00112233445566778899aabbccddeeff
Done
```

### masterkey \<key\>

Set the Thread Master Key value.

```bash
> masterkey 00112233445566778899aabbccddeeff
Done
```

### mode

Get the Thread Device Mode value.

* r: rx-on-when-idle
* s: Secure IEEE 802.15.4 data requests
* d: Full Thread Device
* n: Full Network Data

```bash
> mode
rsdn
Done
```

### mode [rsdn]

Set the Thread Device Mode value.

* r: rx-on-when-idle
* s: Secure IEEE 802.15.4 data requests
* d: Full Thread Device
* n: Full Network Data

```bash
> mode rsdn
Done
```

### neighbor list

List RLOC16 of neighbors.

```bash
> neighbor list
0xcc01 0xc800 0xf000
Done
```

### neighbor table

Print table of neighbors.

```bash
> neighbor table
| Role | RLOC16 | Age | Avg RSSI | Last RSSI |R|S|D|N| Extended MAC     |
+------+--------+-----+----------+-----------+-+-+-+-+------------------+
|   C  | 0xcc01 |  96 |      -46 |       -46 |1|1|1|1| 1eb9ba8a6522636b |
|   R  | 0xc800 |   2 |      -29 |       -29 |1|0|1|1| 9a91556102c39ddb |
|   R  | 0xf000 |   3 |      -28 |       -28 |1|0|1|1| 0ad7ed6beaa6016d |
Done
```

### netdataregister

Register local network data with Thread Leader.

```bash
> netdataregister
Done
```

### netdatashow

Show Thread Leader network data.

```bash
> netdatashow
08040b020000
Done
```

### networkdiagnostic get \<addr\> \<type\> ..

Send network diagnostic request to retrieve tlv of \<type\>s.

If \<addr\> is unicast address, `Diagnostic Get` will be sent.
if \<addr\> is multicast address, `Diagnostic Query` will be sent.

```bash
> networkdiagnostic get fdde:ad00:beef:0:0:ff:fe00:f400 0 1 6
DIAG_GET.rsp: 00088e18ad17a24b0b740102f400060841dcb82d40bac63d

> networkdiagnostic get ff02::1 0 1
DIAG_GET.rsp: 0008567e31a79667a8cc0102f000
DIAG_GET.rsp: 0008aaa7e584759e4e6401025400
```

### networkdiagnostic reset \<addr\> \<type\> ..

Send network diagnostic request to reset \<addr\>'s tlv of \<type\>s. Currently only `MAC Counters`(9) is supported.

```bash
> diagnostic reset fd00:db8::ff:fe00:0 9
Done
```

### networkidtimeout

Get the NETWORK_ID_TIMEOUT parameter used in the Router role.

```bash
> networkidtimeout
120
Done
```

### networkidtimeout \<timeout\>

Set the NETWORK_ID_TIMEOUT parameter used in the Router role.

```bash
> networkidtimeout 120
Done
```

### networkname

Get the Thread Network Name.

```bash
> networkname
OpenThread
Done
```

### networkname \<name\>

Set the Thread Network Name.

```bash
> networkname OpenThread
Done
```

### panid

Get the IEEE 802.15.4 PAN ID value.

```bash
> panid
0xdead
Done
```

### panid \<panid\>

Set the IEEE 802.15.4 PAN ID value.

```bash
> panid 0xdead
Done
```

### parent

Get the diagnostic information for a Thread Router as parent.

Note: When operating as a Thread Router, this command will return the cached
      information from when the device was previously attached as a Thread
      Child. Returning cached information is necessary to support the Thread
      Test Harness - Test Scenario 8.2.x requests the former parent (i.e. Joiner
      Router's) MAC address even if the device has already promoted to a router.

```bash
> parent
Ext Addr: be1857c6c21dce55
Rloc: 5c00
Link Quality In: 3
Link Quality Out: 3
Age: 20
Done
```

### parentpriority

Get the assigned parent priority value, -2 means not assigned.

```bash
> parentpriority
1
Done
```

### parentpriority \<parentpriority\>

Set the assigned parent priority value: 1, 0, -1 or -2.

```bash
> parentpriority 1
Done
```

### ping \<ipaddr\> [size] [count] [interval]

Send an ICMPv6 Echo Request.

* size: The number of data bytes to be sent.
* count: The number of ICMPv6 Echo Requests to be sent.
* interval: The interval between two consecutive ICMPv6 Echo Requests in seconds. The value may have fractional form, for example `0.5`.

```bash
> ping fdde:ad00:beef:0:558:f56b:d688:799
16 bytes from fdde:ad00:beef:0:558:f56b:d688:799: icmp_seq=1 hlim=64 time=28ms
```

### ping stop

Stop sending ICMPv6 Echo Requests.

```bash
> ping stop
Done
```

### pollperiod

Get the customized data poll period of sleepy end device (milliseconds). Only for certification test

```bash
> pollperiod
0
Done
```

### pollperiod \<pollperiod\>

Set the customized data poll period for sleepy end device (milliseconds >= 10ms). Only for certification test

```bash
> pollperiod 10
Done
```

### prefix

Get the prefix list in the local Network Data.

```bash
> prefix
2001:dead:beef:cafe::/64 paros med
Done
```

### prefix add \<prefix\> [pvdcsr] [prf]

Add a valid prefix to the Network Data.

* p: Preferred flag
* a: Stateless IPv6 Address Autoconfiguration flag
* d: DHCPv6 IPv6 Address Configuration flag
* c: DHCPv6 Other Configuration flag
* r: Default Route flag
* o: On Mesh flag
* s: Stable flag
* prf: Default router preference, which may be 'high', 'med', or 'low'.

```bash
> prefix add 2001:dead:beef:cafe::/64 paros med
Done
```

### prefix remove \<prefix\>

Invalidate a prefix in the Network Data.

```bash
> prefix remove 2001:dead:beef:cafe::/64
Done
```

### promiscuous

Get radio promiscuous property.

```bash
> promiscuous
Disabled
Done
```

### promiscuous enable

Enable radio promiscuous operation and print raw packet content.

```bash
> promiscuous enable
Done
```

### promiscuous disable

Disable radio promiscuous operation.

```bash
> promiscuous disable
Done
```

### releaserouterid \<routerid\>
Release a Router ID that has been allocated by the device in the Leader role.

```bash
> releaserouterid 16
Done
```

### reset
Signal a platform reset.

```bash
> reset
```

### rloc16

Get the Thread RLOC16 value.

```bash
> rloc16
0xdead
Done
```

### route

Get the external route list in the local Network Data.

```bash
> route
2001:dead:beef:cafe::/64 s med
Done
```

### route add \<prefix\> [s] [prf]

Add a valid external route to the Network Data.

* s: Stable flag
* prf: Default Router Preference, which may be: 'high', 'med', or 'low'.

```bash
> route add 2001:dead:beef:cafe::/64 s med
Done
```

### route remove \<prefix\>

Invalidate a external route in the Network Data.

```bash
> route remove 2001:dead:beef:cafe::/64
Done
```

### router list

List allocated Router IDs.

```bash
> router list
8 24 50
Done
```

### router table

Print table of routers.

```bash
> router table
| ID | RLOC16 | Next Hop | Path Cost | LQ In | LQ Out | Age | Extended MAC     |
+----+--------+----------+-----------+-------+--------+-----+------------------+
| 21 | 0x5400 |       21 |         0 |     3 |      3 |   5 | d28d7f875888fccb |
| 56 | 0xe000 |       56 |         0 |     0 |      0 | 182 | f2d92a82c8d8fe43 |
Done
```

### router \<id\>

Print diagnostic information for a Thread Router.  The `id` may be a Router ID or an RLOC16.

```bash
> router 50
Alloc: 1
Router ID: 50
Rloc: c800
Next Hop: c800
Link: 1
Ext Addr: e2b3540590b0fd87
Cost: 0
Link Quality In: 3
Link Quality Out: 3
Age: 3
Done
```

```bash
> router 0xc800
Alloc: 1
Router ID: 50
Rloc: c800
Next Hop: c800
Link: 1
Ext Addr: e2b3540590b0fd87
Cost: 0
Link Quality In: 3
Link Quality Out: 3
Age: 7
Done
```

### routerdowngradethreshold

Get the ROUTER_DOWNGRADE_THRESHOLD value.

```bash
> routerdowngradethreshold
23
Done
```

### routerdowngradethreshold \<threshold\>

Set the ROUTER_DOWNGRADE_THRESHOLD value.

```bash
> routerdowngradethreshold 23
Done
```

### routereligible

Indicates whether the router role is enabled or disabled.

```bash
> routereligible
Enabled
Done
```

### routereligible enable

Enable the router role.

```bash
> routereligible enable
Done
```

### routereligible disable

Disable the router role.

```bash
> routereligible disable
Done
```

### routerselectionjitter

Get the ROUTER_SELECTION_JITTER value.

```bash
> routerselectionjitter
120
Done
```

### routerselectionjitter \<jitter\>

Set the ROUTER_SELECTION_JITTER value.

```bash
> routerselectionjitter 120
Done
```

### routerupgradethreshold

Get the ROUTER_UPGRADE_THRESHOLD value.

```bash
> routerupgradethreshold
16
Done
```

### routerupgradethreshold \<threshold\>

Set the ROUTER_UPGRADE_THRESHOLD value.

```bash
> routerupgradethreshold 16
Done
```

### scan \[channel\]

Perform an IEEE 802.15.4 Active Scan.

* channel: The channel to scan on.  If no channel is provided, the active scan will cover all valid channels.

```bash
> scan
| J | Network Name     | Extended PAN     | PAN  | MAC Address      | Ch | dBm | LQI |
+---+------------------+------------------+------+------------------+----+-----+-----+
| 0 | OpenThread       | dead00beef00cafe | ffff | f1d92a82c8d8fe43 | 11 | -20 |   0 |
Done
```

### scan energy \[duration\]

Perform an IEEE 802.15.4 Energy Scan.

* duration: The time in milliseconds to spend scanning each channel.

```bash
> scan energy 10
| Ch | RSSI |
+----+------+
| 11 |  -59 |
| 12 |  -62 |
| 13 |  -67 |
| 14 |  -61 |
| 15 |  -87 |
| 16 |  -86 |
| 17 |  -86 |
| 18 |  -52 |
| 19 |  -58 |
| 20 |  -82 |
| 21 |  -76 |
| 22 |  -82 |
| 23 |  -74 |
| 24 |  -81 |
| 25 |  -88 |
| 26 |  -71 |
Done
```

### singleton
Return true when there are no other nodes in the network, otherwise return false.

```bash
> singleton
true or false
Done
```

### sntp query \[SNTP server IP\] \[SNTP server port\]

Send SNTP Query to obtain current unix epoch time (from 1st January 1970).
The latter two parameters have following default values:
 * NTP server IP: 2001:4860:4806:8:: (Google IPv6 NTP Server)
 * NTP server port: 123

```bash
> sntp query
> SNTP response - Unix time: 1540894725 (era: 0)
```

You can use NAT64 of OpenThread Border Router to reach e.g. Google IPv4 NTP Server:
```bash
> sntp query 64:ff9b::d8ef:2308
> SNTP response - Unix time: 1540898611 (era: 0)
```

### state
Return state of current state.

```bash
> state
offline, disabled, detached, child, router or leader
Done
```

### state <state>
Try to switch to state `detached`, `child`, `router` or `leader`.

```bash
> state leader
Done
```

### thread start

Enable Thread protocol operation and attach to a Thread network.

```bash
> thread start
Done
```

### thread stop

Disable Thread protocol operation and detach from a Thread network.

```bash
> thread stop
Done
```

### thread version

Get the Thread Version number.

```bash
> thread version
2
Done
```

### txpower

Get the transmit power in dBm.

```bash
> txpower
-10 dBm
Done
```

### txpower \<txpower\>

Set the transmit power.

```bash
> txpower -10
Done
```

### version

Print the build version information.

```bash
> version
OPENTHREAD/gf4f2f04; Jul  1 2016 17:00:09
Done
```

### mac retries direct

Get the number of direct TX retries on the MAC layer.

```bash
> mac retries direct
3
Done
```

### mac retries direct \<number\>

Set the number of direct TX retries on the MAC layer.

```bash
> mac retries direct 5
Done
```

### mac retries indirect

Get the number of indirect TX retries on the MAC layer.

```bash
> mac retries indirect
3
Done
```

### mac retries indirect \<number\>

Set the number of indirect TX retries on the MAC layer.

```bash
> mac retries indirect 5
Done
```

### macfilter

List the macfilter status, including address and received signal strength filter settings.

```bash
> macfilter
Address Mode: Whitelist
0f6127e33af6b403 : rss -95 (lqi 1)
0f6127e33af6b402
RssIn List:
0f6127e33af6b403 : rss -95 (lqi 1)
Default rss : -50 (lqi 3)
Done
```

### macfilter addr

List the address filter status.

```bash
> macfilter addr
Whitelist
0f6127e33af6b403 : rss -95 (lqi 1)
0f6127e33af6b402
Done
```

### macfilter addr disable

Disable address filter mode.

```bash
> macfilter addr disable
Done
```

### macfilter addr whitelist

Enable whitelist address filter mode.

```bash
> macfilter addr whitelist
Done
```

### macfilter addr blacklist

Enable blacklist address filter mode.

```bash
> macfilter addr blacklist
Done
```

### macfilter addr add \<extaddr\> \[rss\]

Add an IEEE 802.15.4 Extended Address to the address filter, and fixed the received singal strength for
the messages from the address if rss is specified.

```bash
> macfilter addr add 0f6127e33af6b403 -95
Done
```

```bash
> macfilter addr add 0f6127e33af6b402
Done
```

### macfilter addr remove \<extaddr\>

Remove the IEEE802.15.4 Extended Address from the address filter.

```bash
> macfilter addr remove 0f6127e33af6b402
Done
```

### macfilter addr clear

Clear all the IEEE802.15.4 Extended Addresses from the address filter.

```bash
> macfilter addr clear
Done
```

### macfilter rss

List the rss filter status

```bash
> macfilter rss
0f6127e33af6b403 : rss -95 (lqi 1)
Default rss: -50 (lqi 3)
Done
```

### macfilter rss add \<extaddr\> \<rss\>

Set the received signal strength for the messages from the IEEE802.15.4 Extended Address.
If extaddr is \*, default received signal strength for all received messages would be set.


```bash
> macfilter rss add * -50
Done
```

```bash
> macfilter rss add 0f6127e33af6b404 -85
Done
```

### macfilter rss add-lqi \<extaddr\> \<lqi\>

Set the received link quality for the messages from the IEEE802.15.4 Extended Address. Valid lqi range [0,3]
If extaddr is \*, default received link quality for all received messages would be set.
Equivalent with 'filter rss add' with similar usage


```bash
> macfilter rss add-lqi * 3
Done
```

```bash
> macfilter rss add 0f6127e33af6b404 2
Done
```

### macfilter rss remove \<extaddr\>

Removes the received signal strength or received link quality setting on the Extended Address.
If extaddr is \*, default received signal strength or link quality for all received messages would be unset.

```bash
> macfilter rss remove *
Done
```

```bash
> macfilter rss remove 0f6127e33af6b404
Done
```

### macfilter rss clear

Clear all the received signal strength or received link quality settings.

```bash
> macfilter rss clear
Done
```

### diag

Factory Diagnostics module is enabled only when building OpenThread with `OPENTHREAD_CONFIG_DIAG_ENABLE=1` option.
Go [diagnostics module][DIAG] for more information.

### service

Module for controlling service registration in Network Data.
Each change in service registration must be sent to leader by `netdataregister` command
before taking effect.

### service add \<enterpriseNumber\> \<serviceData\> \<serverData\>

Add service to the Network Data.

```bash
> service add 44970 foo bar
Done
> netdataregister
Done
> ipaddr
fdde:ad00:beef:0:0:ff:fe00:fc10
fdde:ad00:beef:0:0:ff:fe00:fc00
fdde:ad00:beef:0:0:ff:fe00:7c00
fe80:0:0:0:1486:2f57:3c:6e10
fdde:ad00:beef:0:8ca4:19ed:217a:eff9
Done
```

### service remove \<enterpriseNumber\> \<serviceData\>

Remove service from Network Data.

```bash
> service remove 44970 foo
Done
> netdataregister
Done
> ipaddr
fdde:ad00:beef:0:0:ff:fe00:fc00
fdde:ad00:beef:0:0:ff:fe00:7c00
fe80:0:0:0:1486:2f57:3c:6e10
fdde:ad00:beef:0:8ca4:19ed:217a:eff9
Done
```

[DIAG]:../../src/core/diags/README.md
