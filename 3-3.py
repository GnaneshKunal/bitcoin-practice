#!/usr/bin/env python3

from bitcoin.rpc import RawProxy

# Create a connection to local BitCoin Core node
p = RawProxy()

# Run the getblockchaininfo command, sotre the resulting data in info
info = p.getblockchaininfo()

# Retrieve the 'blocks' element from info
print(info['blocks'])
