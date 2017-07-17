###零拷贝
零拷贝（zero copy）技术概述
什么是零拷贝？
简单一点来说，零拷贝就是一种避免 CPU 将数据从一块存储拷贝到另外一块存储的技术。针对操作系统中的设备驱动程序、文件系统以及网络协议堆栈而出现的各种零拷贝技术极大地提升了特定应用程序的性能，并且使得这些应用程序可以更加有效地利用系统资源。这种性能的提升就是通过在数据拷贝进行的同时，允许 CPU 执行其他的任务来实现的。零拷贝技术可以减少数据拷贝和共享总线操作的次数，消除传输数据在存储器之间不必要的中间拷贝次数，从而有效地提高数据传输效率。而且，零拷贝技术减少了用户应用程序地址空间和操作系统内核地址空间之间因为上下文切换而带来的开销。进行大量的数据拷贝操作其实是一件简单的任务，从操作系统的角度来说，如果 CPU 一直被占用着去执行这项简单的任务，那么这将会是很浪费资源的；如果有其他比较简单的系统部件可以代劳这件事情，从而使得 CPU 解脱出来可以做别的事情，那么系统资源的利用则会更加有效。综上所述，零拷贝技术的目标可以概括如下：
避免数据拷贝
避免操作系统内核缓冲区之间进行数据拷贝操作。
避免操作系统内核和用户应用程序地址空间这两者之间进行数据拷贝操作。
用户应用程序可以避开操作系统直接访问硬件存储。
数据传输尽量让 DMA 来做。
将多种操作结合在一起
避免不必要的系统调用和上下文切换。
需要拷贝的数据可以先被缓存起来。
对数据进行处理尽量让硬件来做。
前文提到过，对于高速网络来说，零拷贝技术是非常重要的。这是因为高速网络的网络链接能力与 CPU 的处理能力接近，甚至会超过 CPU 的处理能力。如果是这样的话，那么 CPU 就有可能需要花费几乎所有的时间去拷贝要传输的数据，而没有能力再去做别的事情，这就产生了性能瓶颈，限制了通讯速率，从而降低了网络链接的能力。一般来说，一个 CPU 时钟周期可以处理一位的数据。举例来说，一个 1 GHz 的处理器可以对 1Gbit/s 的网络链接进行传统的数据拷贝操作，但是如果是 10 Gbit/s 的网络，那么对于相同的处理器来说，零拷贝技术就变得非常重要了。对于超过 1 Gbit/s 的网络链接来说，零拷贝技术在超级计算机集群以及大型的商业数据中心中都有所应用。然而，随着信息技术的发展，1 Gbit/s，10 Gbit/s 以及 100 Gbit/s 的网络会越来越普及，那么零拷贝技术也会变得越来越普及，这是因为网络链接的处理能力比 CPU 的处理能力的增长要快得多。传统的数据拷贝受限于传统的操作系统或者通信协议，这就限制了数据传输性能。零拷贝技术通过减少数据拷贝次数，简化协议处理的层次，在应用程序和网络之间提供更快的数据传输方法，从而可以有效地降低通信延迟，提高网络吞吐率。零拷贝技术是实现主机或者路由器等设备高速网络接口的主要技术之一。
现代的 CPU 和存储体系结构提供了很多相关的功能来减少或避免 I/O 操作过程中产生的不必要的 CPU 数据拷贝操作，但是，CPU 和存储体系结构的这种优势经常被过高估计。存储体系结构的复杂性以及网络协议中必需的数据传输可能会产生问题，有时甚至会导致零拷贝这种技术的优点完全丧失。

###说Kafka是下一代分布式消息系统的原因
kafka提倡使用拉模式，并且可以对消息重复消费，看起来不符合传统queue的思想，但却提供了额外的好处，比如：某模块更新到产线发现有bug，需要将上线以来的消息全部重新消费，即消息回溯。
 
kafka是高并发型的消息队列，但这是有前提条件的。条件是topic要定义多个partition，将压力分担到各个partition上。topic是逻辑概念，partition是物理存在各个broker，以此达到负载均衡的目的。要注意的是，各个partition可以独立消费，各partition间的消息是无法保证顺序性的，顺序只存在同一partition。以我的经验看，无论哪种MQ，要严格保证顺序，都要付出昂贵的代价，因此弱化顺序是有必要的。
 
kafka的另一个特性是高可用。放眼目前业界数据层的高可用解决方案，采用的无非都是两种：冗余数据和共享存储。后者以价格昂贵著称，比如SAN，给土豪公司玩的。在党中央构建节约性社会的号召下，我建议使用前者。冗余数据最常见的便是日志复制，kafka的道理也一样。由一组节点组成leader，follower组成小的cluster，由zookeeper做协调(Paxos算法)。leader，follower的比例和数量可配置，一般为1:2。在写入的时候, follower会不断复制leader的数据，leader挂掉后会从follwer中选举新的leader。
 
kafka使用了零拷贝技术来优化性能，直接发送磁盘的数据到socket。此为其极为取巧的设计和亮点。

###MySQL 几个基本操作
1. 创建用户oldboy，使之可以管理数据库oldboy
mysql>grant all on oldboy.* to oldboy@'localhost' identified by '123';

2. 查看创建的用户oldboy拥有哪些权限
mysql>show grants for oldboy@'localhost'\G;

3. 查看当前数据库里有哪些用户
mysql>select user,host from mysql.user;

4. 
delete是逻辑删除表中的数据，一列一列的删除表中数据，速度比较慢
mysql> delete from test;
truncate是物理删除表中的数据，一次性全部都给清空表中数据，速度很快
mysql> truncate table test;