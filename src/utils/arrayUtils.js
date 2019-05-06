const arrayUtils = {
  range(start = 0, end = 0) {
    const items = [];

    for (let i = start; i < end; i += 1) {
      items.push(i);
    }

    return items;
  },
};

export default arrayUtils;
