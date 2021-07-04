module.exports = {
    reactStrictMode: true,
    async rewrites() {
        return [
            {
                source: '/api/devices/mode/1/:path*',
                destination: 'http://192.168.0.245:8000/api/devices/mode/1/:path*' // Proxy to Backend
            }
        ]
    }
}
