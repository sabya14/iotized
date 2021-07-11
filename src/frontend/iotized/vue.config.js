module.exports = {
  transpileDependencies: [
    'vuetify'
  ],
  devServer: {
    open: process.platform === 'darwin',
    host: '192.168.0.245',
    port: 8080, // CHANGE YOUR PORT HERE!
    proxy: {
      '/': {
        target: 'http://192.168.0.245:8000',
        changeOrigin: true
      },
    }
  },
}
