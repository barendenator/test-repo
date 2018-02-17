//
//  Blockchain.cpp
//  BlockChainExample
//
//  Created by Jon on 1/10/18.
//  Copyright © 2018 Crypto Enthusiasts. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <ctime>
#include <string>

#include "include/Block.h"
#include "include/Blockchain.h"

#include <vector>

// Blockchain Constructor
Blockchain::Blockchain()
{
    Block genesis = createGenesisBlock();
    chain.push_back(genesis);
}

// Public Chain Getter
std::vector<Block> Blockchain::getChain() {
    return chain;
}

// Create Genesis Block
Block Blockchain::createGenesisBlock()
{
    // Get Current Time
    std::time_t current;
    
    // Setup Initial Transaction Data
    TransactionData d(0, "Genesis", "Genesis", time(&current));
    
    // Return Genesis Block
    Block genesis(0, d, 0);
    return genesis;
}

// We only need pointer here
// to demonstrate manipulation of transaction data
Block *Blockchain::getLatestBlock()
{
    return &chain.back();
}

void Blockchain::addBlock(TransactionData d)
{
    int index = (int)chain.size();
    std::size_t previousHash = (int)chain.size() > 0 ? getLatestBlock()->getHash() : 0;
    Block newBlock(index, d, previousHash);
    chain.push_back(newBlock);
}

bool Blockchain::isChainValid()
{
    std::vector<Block>::iterator it;
    
    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        if (!currentBlock.isHashValid())
        {
            return false;
        }
        
        // Don't forget to check if this is the first item
        if (it != chain.begin())
        {
            Block previousBlock = *(it - 1);
            if (currentBlock.getPreviousHash() != previousBlock.getHash())
            {
                return false;
            }
        }
    }
    
    return true;
}

void Blockchain::printChain() {
    std::vector<Block>::iterator it;
    
    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        std::cout << "\n\nBlock ===================================";
        std::cout << "\nIndex:" << currentBlock.getIndex();
        std::cout << "\nAmount:" << currentBlock.data.amount;
        std::cout << "\nSenderKey:" << currentBlock.data.senderKey.c_str();
        std::cout << "\nReceiverKey: " << currentBlock.data.receiverKey.c_str();
        std::cout << "\nTimestamp: " << currentBlock.data.timestamp;
        std::cout << "\nHash: " << currentBlock.getHash();
        std::cout << "\nPrevious Hash: " << currentBlock.getPreviousHash();
        std::cout << "\nIs Block Valid?: " << currentBlock.isHashValid();
    }
}

