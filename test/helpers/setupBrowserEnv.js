// https://github.com/avajs/ava/blob/master/docs/recipes/browser-testing.md

import browserEnv from 'browser-env';

browserEnv();

// Node.js does not have requestIdleCallback, for tests replace it with similar
// Node.js utility global.setImmediate
window.requestIdleCallback = setImmediate;
