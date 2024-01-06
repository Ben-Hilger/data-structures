function linearSearch(haystack: number[], needle: number): boolean {
    for (let i = 0; i < haystack.length; i++) {
        if (haystack[i] == needle) {
            return true;
        }
    }
    return false;
}

console.log(linearSearch([1, 2, 3, 4, 5], 1));
console.log(linearSearch([1, 2, 3, 4, 5], 2));
console.log(linearSearch([1, 2, 3, 4, 5], 3));
console.log(linearSearch([1, 2, 3, 4, 5], 4));
console.log(linearSearch([1, 2, 3, 4, 5], 5));
console.log(linearSearch([1, 2, 3, 4, 5], 6));
