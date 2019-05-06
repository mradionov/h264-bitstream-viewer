export default {
  require: [
    // https://github.com/avajs/ava/blob/master/docs/recipes/es-modules.md
    'esm',

    // https://github.com/avajs/ava/blob/master/docs/recipes/browser-testing.md
    './test/helpers/setupBrowserEnv.js',
  ],
};
