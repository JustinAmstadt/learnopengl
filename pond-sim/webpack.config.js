const HtmlWebpackPlugin = require('html-webpack-plugin');

module.exports = {
    entry: './src/index.ts',
    output: {
        path: __dirname + '/dist',
        filename: 'bundle.js',
    },
    devServer: {
        static: './dist',
        port: 9000,
    },
    plugins: [
        new HtmlWebpackPlugin({
            template: './index.html',
        }),
    ],
    resolve: {
        extensions: ['.ts', '.js'], // Resolve these file extensions
    },
    mode: "development",
    module: {
        rules: [
            {
                test: /\.ts$/, // Apply this rule to .ts files
                use: 'ts-loader', // Use ts-loader for TypeScript files
                exclude: /node_modules/, // Exclude node_modules
            },
            {
              test: /\.(png|jpe?g|gif|svg)$/i, // regex to match image files
              use: [
                {
                  loader: 'url-loader',
                  options: {
                    limit: 8192, // Convert images < 8kb to base64 strings
                    name: '[name].[hash].[ext]', // output file name format
                    outputPath: 'images', // output directory for images
                  },
                },
              ],
            },
          ],
      },
};
