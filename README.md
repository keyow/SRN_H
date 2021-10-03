# Secure Recursive Net - Hashable (SRN_H)

**SRN_H** is an algorythm that allows user form hashes from random string, picture, etc.

The basis of the algorythm contains three diffirent hash-algorythms: MD5,
SHA (128 bit implementation) and SRN algorythm (it is an encryption algorythm by itself,
but it's encryption version with *random* recursive functions is good to use).

### Idea
The main idea of an algorythm is to use diffirent hash-algorythms one after another.
The key feature consists in three blocks: 128-bit algorythms, 256-bit algorythms, SRN-128 (it can adapt for 128, 256, 512 bit algorythms)
The sequence depends on the message characteristic called *P(message)*.
For example, P(message) = x, so it gives us the sequence like *(0, 1, 1), (2, 3, 3), 4*.
It means that we are going to use 128-bit algorythm with index 0, after it we use two 128 bit algorythms with index 1.
After that we execute 256 bit algorythms, and in the end we execute SRN-256 (the hash prototype of an SRN-256 will be pushed soon).
