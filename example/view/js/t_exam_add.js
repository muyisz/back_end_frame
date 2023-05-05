let addBtn = document.querySelector(".addBtn");
let addBox = document.querySelector(".add");
let autoBtn = document.querySelector(".autoBtn");

// 每一个题目后面都有一个按钮，此处使用querySelectorAll获取，返回的是一个伪数组(元素集合)，使用时可以使用对应的下标，或者修改此获取方法
let choiceBtn = document.querySelectorAll(".choiceBtn");

var subjectList = new Array();

// .add 盒子显示
function boxShow() {
    addBox.style.display = "block";
    $.ajax({
        type: 'get',
        url: '/subject/list',
        success: function (res) {
            if (res.code != 0) {
                alert(res.message)
            } else {
                var data = ""
                for (i = 0; i < res.subjectList.length; i++) {
                    var cell = '<tr><td class="question"><p>' + res.subjectList[i].name + '</p></td><td class="difficulty">L1</td><td class="choose"><button onclick=choice(' + res.subjectList[i].id + ',"' + res.subjectList[i].name + '","' + res.subjectList[i].anwser + '")>选择</button></td></tr>'
                    data += cell
                }
                document.getElementById("subjectList").innerHTML = data
            }
        }
    })
}

// 添加题目按钮点击后题目列表出现
addBtn.onclick = boxShow;

// 第一个“选择” 按钮  手动生成
function choice(id, name, anwser) {
    subjectList[subjectList.length] = {
        id: id,
        name: name,
        anwser: anwser,
    }
    showSubjectList()
}

function showSubjectList() {
    var data = ""
    for (i = 0; i < subjectList.length; i++) {
        var cell = '<div class="exam_item"><div class="question">题目：<textarea name="question" id="" cols="30" rows="1">' + subjectList[i].name + '</textarea></div><div class="answer">答案：<textarea name="answer" id="" cols="30" rows="1">' + subjectList[i].anwser + '</textarea></div></div>'
        data += cell
    }
    document.getElementById("chooseSubjectList").innerHTML = data
    console.log(finBtn)
}

// "自动生成" 按钮
function auto() {

}

// “自动生成” 按钮
autoBtn.onclick = auto;

function submit() {
    var idList = new Array();
    for (i = 0; i < subjectList.length; i++) {
        idList[i] = subjectList[i].id
    }
    let postData = {
        subjectList: idList,
        creater: "admin",
        facilityValue: 1,
    }
    $.ajax({
        type: 'post',
        url: '/test_paper/create',
        dataType: 'json',
        data: JSON.stringify(postData),
        success: function (res) {
            if (res.code != 0) {
                alert(res.message)
            } else {
                window.location.href = '/subject/list_pages'
            }
        }
    })
}

let finBtn = document.querySelector(".finBtn");
finBtn.onclick = submit;

