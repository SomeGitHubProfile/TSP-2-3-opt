const fs = require('fs')

function prettifyJson(data) {
    const r1 = /(?<="vertices": \[[^\]]*)\s+(?=[^\]]*\])/g
    const r2 = /(?<="vertices": \[)\s+|\s+(?=\])/g

    data = data.replace(r1, ' ')
    data = data.replace(r2, '')
    return data
}

function modifyFile(filename) {
    try {
        const data = fs.readFileSync(filename, 'utf-8')
        const prettifiedJson = prettifyJson(data)
        fs.writeFileSync(filename, prettifiedJson, 'utf-8')
    } catch (err) {
        console.error(`Error: ${err.message}`);
    }
}


function main() {
    if (process.argv.length < 3) {
        console.log('Filename is required. Usage: node script.js <filename>')
        return
    }

    const filename = process.argv[2]
    if (!fs.existsSync(filename)) {
        console.log(`Error: The file '${filename}' does not exist.`)
        return
    }
    modifyFile(filename)
};

main()
