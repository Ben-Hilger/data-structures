function binarySearch(haystack: number[], needle: number): boolean {
    
    let low = 0;
    let high = haystack.length;

    do {
        const mid = Math.floor(low + (high-low) / 2);
        const value = haystack[mid];
        if (value === needle) {
            return true;
        } else if (value > needle) {
            high = mid;
        } else if (value < needle) {
            low = mid + 1;
        }
    } while(low < high);

    return false;
}

console.log(binarySearch([1, 2, 3, 4, 5], 1));
console.log(binarySearch([1, 2, 3, 4, 5], 2));
console.log(binarySearch([1, 2, 3, 4, 5], 3));
console.log(binarySearch([1, 2, 3, 4, 5], 4));
console.log(binarySearch([1, 2, 3, 4, 5], 5));
console.log(binarySearch([1, 2, 3, 4, 5], 6));
