This is an early, raw draft of an idea I had in San Diego during LWG session Friday afternoon when I finally had a few hours to think about something other than Ranges. No, it has not been implemented - but I see no great technical barrier to doing so. I'm circulating this to get some early feedback and/or have someone point out horrible technical flaws that I've missed before I invest too much into the idea.

Problem Statement
=================

I am, despite my short history in WG21, already tired of dealing with the issue of name collisions when we add new names to the Standard Library with each revision of C++. Our current policy is to guess at which names we think may be problematic, and then either (1) pick an inferior name in the hopes that it will cause fewer problems, or (2) keep the "good" name but introduce it into a nested namespace inside `std`. For a recent example, [P0631R4 "Math Constants"](https://wg21.link/p0631r4) adds definitions of common mathematical constants to the standard library such as `pi` and `e`. (1) is not a satisfactory solution for library designers: "the obviously correct name has the potential for collisions, pick a poor name instead" and consequently users must search cppreference to find out what the Standard Library calls "pi". (2) unsurprisingly *still* has the potential to introduce name collisions with the nested namespace name. P0631R4 uses a nested namespace `math` which is still likely result in name collisions, albeit fewer than `pi` or `e`.

Sentiment in LEWG is leaning toward the idea that users who write `using namespace std;` are asking for name collisions, that they shouldn't do this "bad" thing, and that it shouldn't be our problem to fix their programs for them if they do so. As the number of names in the Standard Library grows over time, and the amount of user code grows as well, neither (1) nor (2) is a sustainable solution. Using either results in future revisions of C++ intentionally obfuscating standard library names to avoid potential collisions. We either pick names like `std::frobnozzle`, or we introduce `std::math::stuff::things::other::student_t_distribution` in C++32 to avoid breaking the naughty users who wrote `using namespace std::math::stuff::things;` in their C++29 programs because typing out `std::math::stuff::things::eigenvalue` is too high a bar for ease of use. Users who can't be bothered to prefix names with `std::` certainly aren't going to qualify them with `std::math::`, and the vicious cycle continues.

There have even been rumbles about deprecating `using namespace std;` to *force* users to either fully qualify names they use in the standard library or write using declarations for individual names. I can't imagine this kind of adversarial tactic being well-received by users. What if, instead of harming ease of use by trying to get users to stop doing this thing we want them to not do, we gave them something to do instead?

Shadow namespaces
=================

Since users cannot be bothered to write using declarations for the names they use in the standard library, why don't we do it for them? I propose adding nested namespaces to C++20 named `cpp17` and `cpp20` (NB: we should simultaneously zombify `cpp\d+` for past and future standardization to defend against macroization of these names). A standard library header that defines an entity `std::foo::bar::baz` according to the C++XX standard also defines namespaces `std::cppXX::foo` and `std::cppXX::foo::bar` and inserts a using declaration:
```c++
namespace std::cppXX::foo::bar {
    using std::foo::bar::baz;
}
```
Effectively, `std::cpp17` presents a view of the name structure of the standard library as of C++17, and likewise for `std::cpp20`. The meaning of those names may change in future revisions of C++, but the set of visible names will not.

Users who write `using namespace std;` should be encouraged - [possibly by a compiler warning](https://i.imgflip.com/2n1mwr.jpg) - to instead write `using namespace std::cpp20;`. Since the set of names in `std::cpp20` will not change in future standard revisions, the program is now immune to name collisions from the addition of new standard library names to `std`. Similarly, users with legacy `using namespace std;` code that encounters collisions in C++20 can be encouraged to change that using directive to `using namespace std::cpp17;`. Their code that successfully compiled under C++17 then continues to do so with C++20. Users can choose either to transition from `std::cppXX` to `std::cppXX+1` TU-by-TU at their own pace, or continue to use `std::cppXX` in the expectation that their vendor(s) will continue to support it.

Instead of demanding that users do not write `using namespace std;`, we can give them an alternative that is equally efficient for them - keystrokes are precious! - and doesn't put WG21 in the position of choosing poor names or slowly creeping down into more deeply nested namespaces to avoid name collisions.

* `std::cppXX` or `stdXX`?
* How many such shadow namespaces should the Standard require? My thinking is to require the "current" and "last" Standard revisions, and drop older revisions. The zombification of `std::cpp\d+` / reservation of `std\d+` allows vendors to continue to support older revisions indefinitely as they wish or add shadow namespaces back to C++98 as desired. WG21 will need decide to whether to add more digits in 2098 or require vendors to drop `cpp98` - I don't think that's a problem this proposal needs to solve.
