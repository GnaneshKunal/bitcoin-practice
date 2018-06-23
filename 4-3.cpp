#include <bitcoin/bitcoin.hpp>

int main(void) {
  bc::ec_secret decoded;
  bc::decode_base16(decoded,
		    "038109007313a5807b2eccc082c8c3fbb988a973cacf1a7df9ce725c31b14776");

  bc::wallet::ec_private secret(
				decoded,
				bc::wallet::ec_private::mainnet_p2kh);

  // Get Public Key
  bc::wallet::ec_public public_key(secret);
  std::cout << "Public key: " << public_key.encoded() << std::endl;

  // Create Bitcoin address.
  // Normally you can use:
  // bc:::wallet payment_address payaddr =
  //     public_key.to_payment_address(
  //         bc::wallet::ec_public::mainnet_p2kh);
  // const std::string address = payaddr.encoded();

  // compute hash of public key for2PKH address.
  bc::data_chunk public_key_data;
  public_key.to_data(public_key_data);
  const auto hash = bc::bitcoin_short_hash(public_key_data);

  bc::data_chunk unencoded_address;
  // Reserve 25 Bytes
  //     [Version: 1    ]
  //     [Hash:20     ]
  //    [ checksum:4     ]
  unencoded_address.reserve(25);
  unencoded_address.push_back(0);
  // Hash Data
  bc::extend_data(unencoded_address, hash);
  // Checksum is computed by hashing data, and adding 4 bytes from hash.
  bc::append_checksum(unencoded_address);
  // Finally we must encode the result in Bitcoin's base58 encoding.
  assert(unencoded_address.size() == 25);
  const std::string address = bc::encode_base58(unencoded_address);
  std::cout << "Address: " << address << std::endl;

  return 0;
}
