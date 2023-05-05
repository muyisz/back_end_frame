let editBtn = document.querySelector(".edit");
let delBtn = document.querySelector(".del");
let lookBtn = document.querySelector(".look");

// 编辑
function edit() {

}

// 删除
function del() {

}

// 查看
function look() {

}

// 编辑
editBtn.onclick = edit;

// 删除
delBtn.onclick = del;

// 查看
lookBtn.onclick = look;

function editExam(id){
    window.location.href = '/subject/list_pages?id='+id
}

function getExamList(){
    $.ajax({
        type: 'get',
        url: '/test_peper/list',
        success: function (res) {
            if(res.code!=0){
                alert(res.message)
            }else{
                var data="" 
                for(i=0;i<res.testPaperList.length;i++){
                    var cell='<tr><td>xxx</td><td>'+res.testPaperList[i].id+'</td><td>'+res.testPaperList[i].creater+'</td><td>L0</td><td class="operate"><button onclick="editExam('+res.testPaperList[i].id+')">编辑</button><button class="del">删除</button><button class="look">查看</button></td></tr>'
                    data+=cell
                }
                document.getElementById("examList").innerHTML = data
            }
        }
    })
}

window.onload = getExamList()