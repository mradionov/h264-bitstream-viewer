const path = require('path');

const HTMLWebpackPlugin = require('html-webpack-plugin');
const VueLoaderPlugin = require('vue-loader/lib/plugin');

const rootDir = path.join(__dirname);

const config = {
  mode: 'development',
  entry: {
    main: path.join(rootDir, 'src/main.js'),
  },
  module: {
    rules: [
      {
        test: /\.vue$/,
        loader: 'vue-loader',
      },
      // This will apply to both plain `.css` files and `<style>` block
      // in `.vue` files
      {
        test: /\.css$/,
        use: [
          'vue-style-loader',
          {
            loader: 'css-loader',
            options: {
              modules: true,
              camelCase: true,
              localIdentName: '[name]__[local]__[hash:base64:5]',
            },
          },
        ],
        exclude: /node_modules/,
      },
      // Vendor CSS from node_modules/, don't CSS-module them
      {
        test: /\.css$/,
        use: ['style-loader', 'css-loader'],
        include: /node_modules/,
      },
    ],
  },
  plugins: [
    new HTMLWebpackPlugin({
      template: path.join(rootDir, 'src', 'index.html'),
      hash: true,
    }),
    new VueLoaderPlugin(),
  ],
  resolve: {
    extensions: ['.js', '.vue', '.json'],
  },
};

module.exports = config;
