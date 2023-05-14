SubjectCompletion = 1;
SubjectChoice = 2;
SubjectProgram = 3;

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
    id = Params["id"]
    $.ajax({
        type: 'get',
        url: '/test_paper/detail?id=' + id,
        success: function (res) {
            if (res.code != 0) {
                alert(res.message)
            } else {
                var data = ""
                for (i = 0; i < res.testPaperDetail.subjectList.length; i++) {
                    cell = ""
                    if (res.testPaperDetail.subjectList[i].type == SubjectCompletion) {
                        cell = '<div class="exam_item"><div class="question"> <p>' + res.testPaperDetail.subjectList[i].content + '</p></div><div class="answer"><input type="text"  id="' + res.testPaperDetail.subjectList[i].id + '"></div></div>'
                    }
                    if (res.testPaperDetail.subjectList[i].type == SubjectChoice) {
                        var chooseData = res.testPaperDetail.subjectList[i].answer.split("-")
                        cell = '<div class="exam_item">'+
                        '<div class="question">'+
                        '<p>' + res.testPaperDetail.subjectList[i].content + '</p>'+
                        '</div>'+
                        '<div class="option">'+
                        '<ol>'+
                        '<li class="A">' + chooseData[1] + '</li>'+
                        '<li class="B">' + chooseData[2] + '</li>'+
                        '<li class="C">' + chooseData[3] + '</li>'+
                        '<li class="D">' + chooseData[4] + '</li>'+
                        '</ol>'+
                        '</div>'+
                        '<div class="answer">'+
                        '<div class="answer_text">'+
                        '<input type="text" id="' + res.testPaperDetail.subjectList[i].id + '">'+
                        '</div>'+
                        '</div>'+
                        '</div>'
                    }
                    if (res.testPaperDetail.subjectList[i].type == SubjectProgram) {
                        cell = '<div class="exam_item"><div class="question">' +
                            '<p>' + res.testPaperDetail.subjectList[i].content + '</p>' +
                            '</div>' +
                            '<div class="option">' +
                            '<h4>输入样例</h4>' +
                            '<textarea name="" id="" cols="30" rows="10" readonly>' + res.testPaperDetail.subjectList[i].test.in + '</textarea>' +
                            '</div>' +
                            '<div class="answer">' +
                            '<div class="answer_example">' +
                            '<h4>输出样例</h4>' +
                            '<textarea name="" id="" cols="30" rows="10" readonly>' + res.testPaperDetail.subjectList[i].test.out + '</textarea>' +
                            '</div>' +
                            '</div>' +
                            '答案</br>' +
                            '<textarea type="text" id="' + res.testPaperDetail.subjectList[i].id + '" cols="60" rows="50"> </textarea>' +
                            '</div>'
                    }
                    data += cell
                }
                document.getElementById("test").innerHTML = data
            }
        }
    })
}

function submit() {
    let url = window.location.search
    Params = getUrlParams(url)
    id = Params["id"]
    $.ajax({
        type: 'get',
        url: '/test_paper/detail?id=' + id,
        success: function (res) {
            if (res.code != 0) {
                alert(res.message)
            } else {
                var Data = new Array()
                for (i = 0; i < res.testPaperDetail.subjectList.length; i++) {
                    Data[i] = {
                        id: res.testPaperDetail.subjectList[i].id,
                        anwser: $('#' + res.testPaperDetail.subjectList[i].id).val()//.replace(/[\n\r]/g,'\n'),
                    }
                }
                let postData = {
                    subjectList: Data,
                }
                $.ajax({
                    type: 'post',
                    url: '/test_paper/submit',
                    dataType: 'json',
                    data: JSON.stringify(postData),
                    success: function (res) {
                        if (res.code != 0) {
                            alert(res.message)
                        } else {
                            alert(res.score)
                        }
                    }
                })

            }
        }
    })
}

window.onload = getExam()