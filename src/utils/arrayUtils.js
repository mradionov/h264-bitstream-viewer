const arrayUtils = {
  range(start = 0, end = undefined) {
    if (end === undefined) {
      end = start;
      start = 0;
    }

    const items = [];

    for (let i = start; i < end; i += 1) {
      items.push(i);
    }

    return items;
  },

  concatUint8Arrays(...arrays) {
    const size = arrays.reduce((sum, arr) => {
      return sum + arr.length;
    }, 0);

    const result = new Uint8Array(size);

    let offset = 0;

    arrays.forEach((array) => {
      result.set(array, offset);
      offset += array.length;
    });

    return result;
  },
};

export default arrayUtils;
