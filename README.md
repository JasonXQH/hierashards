HieraChain is a Scalable Permissioned Blockchain System with Hierarchical Sharding

[2022.09.15]v0.0.1版本发布，在fisco 2.8.0基础上增加了跨群组通信功能，需要安装protubuf库(推荐3.11.2版本)

[2022.09.18]v0.0.2版本发布，修复了v0.0.1版本中分片1以外分片的片内共识无法正常运行的问题，提供了组成3分片的节点样例文件

[2022.10.17]v0.0.3.1版本发布，将fisco的共识和执行初步解耦开，共识模块只负责定序; 测试交易能够通过链的源代码发送，避免SDK重发交易的问题

[2022.10.19]v0.0.3.2版本发布，允许读写集未被阻塞的片内交易在共识过程中依然能够被执行，并将执行结果落盘

[2022.10.21]v0.0.3.3版本发布，将fisco的共识和执行功能完全解耦开（先共识后执行），解决此时sdk发送交易无法获取交易回执的问题
