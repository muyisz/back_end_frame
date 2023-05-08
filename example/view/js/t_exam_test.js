

function getUrlParams(url) {
    let urlStr = url.split('?')[1]
    let obj = {};
    let paramsArr = urlStr.split('&')
    for (let i = 0, len = paramsArr.length; i < len; i++) {
        let arr = paramsArr[i].split('=')
        obj[arr[0]] = arr[1];
    }
    return obj
}

function getExam() {
    let url = window.location.search
    Params = getUrlParams(url)
}

window.onload = getExam()