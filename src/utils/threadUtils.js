const threadUtils = {
  // https://developers.google.com/web/updates/2015/08/using-requestidlecallback
  // Safari does not have it yet. Also used when runinng units tests because
  // Node does not have it either.
  requestIdleCallback:
    window.requestIdleCallback ||
    function(cb) {
      const start = Date.now();
      return setTimeout(function() {
        cb({
          didTimeout: false,
          timeRemaining: function() {
            return Math.max(0, 50 - (Date.now() - start));
          },
        });
      }, 1);
    },
};

export default threadUtils;
