---
pagetitle: I Stream, You Stream, We All Stream for istream_iterator
title: I Stream, You Stream, We All Stream for `istream_iterator`
...

### Abstract

The specification and design of `istream_iterator` have some problems. Firstly, the specification in the Standard begins with two paragraphs ([istream.iterator]/1 and /2) that intermix semi-normative description with actual normative requirements. These normative requirements should be in the specification of the individual member functions, resulting in either redundant or "remote" requirements. This situation is both confusing and inconsistent with the specification of other library components.

Second, the semantics of exactly when an `istream_iterator` performs a read from its underlying input stream are unclear. The specification purports to allow an implementation to delay reading the initial value from the stream, which has been a source of confusion in the past ([LWG 245 "Which operations on `istream_iterator` trigger input operations?"](http://cplusplus.github.io/LWG/lwg-closed.html#245)). We argue that an implementation that does so cannot, in fact, conform to the specification.

Whilst correcting these two specification problems we also propose some cleanup and modernization of the specification of `istream_iterator` in passing.

### Discussion

#### `istream_iterator`'s jumbled introduction

The presentation of many Standard Library classes follows a common structure:

* a paragraph with a brief general introduction
* a class synopsis
* a few paragraphs of class-specifiec normative requirements ("template parameter T must be an object type that meets the Destructible requirements", "template parameter T may be an incomplete type")
* a detailed specification of the class's member functions and their individual behaviors

`istream_iterator` does not follow that structure, despite appearing to do so. Its introductory paragraphs are *not* brief, and verge on tutorial: "It is impossible to store things into istream iterators." It contains normative requirements that in some cases duplicate requirements in the specification of the individual member functions ("Two end-of-stream iterators are always equal"), and in other cases are the only occurrence of a requirement that *should* appear in the specification of a member function ("If the iterator fails to read and store a value of `T` (`fail()` on
the stream returns `true`), the iterator becomes equal to the end-of-stream iterator value"). Removing duplicate requirements and relocating non-duplicate requirements to the specification of the entity to which they apply would greatly improve the quality of the specification.

#### Delayed-initialization semantics

### Proposed Solution

### Technical Specification


#### Acknowledgments

I would like to thank Tim Song for pointing out to me that `istream_iterator::operator*` requires the iterator to not be an end-of-stream iterator, and that this requirement is NOT in [istream.iterator.ops] with the specification of `operator*` (where I daresay a sane person might expect it to be) but squirreled away in [istream.iterator]/1.
