// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 5000;

namespace Checkpoints
{
	typedef std::map<int, uint256> MapCheckpoints;

	//
	// What makes a good checkpoint block?
	// + Is surrounded by blocks with reasonable timestamps
	//   (no blocks before with a timestamp after, none after with
	//    timestamp before)
	// + Contains no strange transactions
	//
	static MapCheckpoints mapCheckpoints =
		boost::assign::map_list_of
		(0, uint256("0x0000ebc8051bff80f7946f4420efb219e66f66b89fdc1df0ed8a30b428bf0033"))
		(1045, uint256("0x098c3515912a25c16deab0390c43091505879078b7334f098222dd3bfa31b6ad"))
		(1954, uint256("0x1b9fc5db67f518272473649364583f560e5fd4ea7372d564c4ab2231a06fd2c4"))
		(2547, uint256("0xa154a82676f609dcd17e22c7ca4079916c4e4e2f4f64105318a4fad294484cc7"))
		(2978, uint256("0x14d413fcfa6396a3a538709ff66ac9a05329223c7a46d7f78b4f1834dd402f93"))
		(5489, uint256("0x674e9e168db0e3bc285ddab44e8199c8eb67a96525c94fc31ba4447d6cefd008"))
		(11458, uint256("0x7f8d98aa499e411f3e1be53ad75d8149b8d09656eb7df1e7540822cbf211754e"))
		(19745, uint256("0xabb199272fdecbf56a3af3bff7891d03cb34d51c1d404bce9b34a4d425834bff"))
		(28547, uint256("0x86ed3ab436ddc29d2735304633e2c6e76b20ed36a55d866bc06d390569df078e"))
		(36900, uint256("0x1be79a0933ef2c5424eda67ac927c78f540d38e73defa06b55d789338f89bcd9"))
		(49875, uint256("0xb4e775992616abd8534c5887d35851ee789ba26ce881bd7df2aae2801a605760"))
		(54208, uint256("0xdccf9542d6928cfdf67547d024696b68818dcd64cb2cb3ac325a98ce15a45406"))
		(67321, uint256("0xd5ed85a8727484b2b905890306f92996482935853be14740165432cf8db532ec"))
		(82123, uint256("0xdd4cd1b4a6279a67aaf6a9ccaae610215f02fd384c98b551eb16103b37bf83b6"))
		(127845, uint256("0x449d67f1a1a573636bcf0c3e25ae6923aac4a1bc2424576cf1b2db34500d147f"))
		(172698, uint256("0xde770660f42f02b7d7245bbb07a7bd5bd0c2c2881556c92aa6ac3bcd848003e0"))
		(212367, uint256("0x3d277d2f11cf6b2a984e81b0a60f40eae268e4e0628960c9471f4e12423bb220"))
		(259784, uint256("0xe422c202cd88430d776f01b926a928ae998c0357647e1627e501d0b224a48ebc"))
		(332453, uint256("0x97c57d3f26d2ab73e1faf0624aef639f6dec75dc56dfddeb17216ad86532b7e5"))
		(384201, uint256("0x2f716bb3aa37b23e0b483ed0fe265b81f332eaa5bf2b853446c786b1b2fea881"))
		(398729, uint256("0xb112dcd53c63545532b7b1b3d129e74242c53f7762cc0d32f9fc7b8a4d325ab9"))
		(414968, uint256("0xebc7ecb479cc0fede3a8d09d7928165b63b3781efec64e6c8f554a912f06776a"))
		(459277, uint256("0x063aada361f8dabb0db4cfc266e2a3489b1942dbf8562258bc55204a7abc4a8f"))
		(414968, uint256("0xebc7ecb479cc0fede3a8d09d7928165b63b3781efec64e6c8f554a912f06776a"))
		(491495, uint256("0x22ecb92a25ce0cfa2b6ddf663aca8280e8556cb9eb71565cdb00695806378782"))		
		(491498, uint256("0xd5b2660e6171842a58dadd9ce5806dc0129893fef2af409a706c841a8c85b81b"))
		(491499, uint256("0x17fded770a8145717c194dd438c7ebf26fae647551304e0c86e1cf6701ab2445"))
		(491500, uint256("0x66bcf845cdfd9819f0b3ee2a36ce73dd15232f55f77806c0a36db9f6b8b547e1"))
		(491501, uint256("0xefc343373f59d20afab4603de2de4f751a6885ec60910b3d7906f203b3980894"))
		(491505, uint256("0x59138bb40f068f504cf19ba9932a779d9a22705c8c7c5fb3b03eca85e2598d2b"))
		(491508, uint256("0x527b1a186ff5f4746222fd3495868d0e12ff045d355efa316ccc912c8e3eedfe"))
		(491510, uint256("0x40c401f249b30ee59c51f8904f332ac1f44e4d1d5fc56dd97a70e2d4e03f28e5"))
		(491513, uint256("0x2e70bf4bdf7d045e602af36d9a6296d23b1e72f11dca54a9153aadcbf5f56233"))
		(491526, uint256("0xc0aa2102f98d30651761b122c54cac02d6ab861c64d023a21a423af5c29aab06"))
		(491532, uint256("0x4830eac7f8a1082bbbc7abb2d95c452f3f8458b98541477c2264a61e9c69ce19"))
		(491541, uint256("0x10fc9f9603062ebca872583d0763f0dbf7fc183b0ea1cad5d784b3f1450ec01a"))
		;

	// TestNet has no checkpoints
	static MapCheckpoints mapCheckpointsTestnet;

	bool CheckHardened(int nHeight, const uint256& hash)
	{
		MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

		MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
		if (i == checkpoints.end()) return true;
		return hash == i->second;
	}

	int GetTotalBlocksEstimate()
	{
		MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

		if (checkpoints.empty())
			return 0;
		return checkpoints.rbegin()->first;
	}

	CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
	{
		MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

		BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
		{
			const uint256& hash = i.second;
			std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
			if (t != mapBlockIndex.end())
				return t->second;
		}
		return NULL;
	}

	// Automatically select a suitable sync-checkpoint 
	const CBlockIndex* AutoSelectSyncCheckpoint()
	{
		const CBlockIndex *pindex = pindexBest;
		// Search backward for a block within max span and maturity window
		while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
			pindex = pindex->pprev;
		return pindex;
	}

	// Check against synchronized checkpoint
	bool CheckSync(int nHeight)
	{
		const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
		if (nHeight <= pindexSync->nHeight) {
			return false;
		}
		return true;
	}
}
