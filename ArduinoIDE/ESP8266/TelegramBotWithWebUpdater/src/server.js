
const express = require('express')
const path = require('path')

// const favicon = require('serve-favicon')
const PORT = 7070;

const app = express()

app.use(express.json())

app.use(express.static(path.resolve(__dirname, 'static')))
// app.use(favicon(path.join(__dirname,'static','favicon.ico')))

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname,'static','index.html'))
})
app.get('/led1', (req, res) => {
    res.redirect('/')
})
app.get('/update', (req, res) => {
    res.send('Этот роут заглушка для разработки')
})
app.get('/echo', (req, res) => {
    res.sendFile(path.join(__dirname,'static','echo.json'))
})


const start = async () => {
    try {
        app.listen(PORT, () => console.log(`Server run: http://localhost:${PORT}`))
    }catch (e) {
        console.log(e)
    }
}

start()
