# Secure Recursive Net - Hashable (SRN_H)

**SRN_H** is an algorythm that allows user form hashes from random string, picture, etc.

The basis of the algorythm contains three diffirent hash-algorythms: MD5,
SHA (128 bit implementation) and SRN algorythm (it is an encryption algorythm by itself,
but it's encryption version with *random* recursive functions is good to use).

### Idea
The main idea of an algorythm is to use diffirent hash-algorythms one after another.
The sequence depends on the message characteristic called *P(message)*.
For example, P(message) = x, so it gives us the sequence like *0, 1, 1, 1, 2, 0, 2*.
It means that we are going to use MD5, SHA, SHA, SHA, SRN, MD5, SRN algorythms *one by one*.
