module main

struct Array {
mut:
    data []u32
    size int
    ref_c int
    id   int
}
struct ArrayParam {
    data []Array
    size int
}
