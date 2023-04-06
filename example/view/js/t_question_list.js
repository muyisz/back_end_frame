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

function getQuestionList(){
    alert(1)
    $.ajax({
        type: 'get',
        url: '/subject/list',
        success: function (res) {
            if(res.code!=0){
                alert(res.message)
            }else{
                var data="" 
                for(i=0;i<res.subjectList.length;i++){
                    var type=""
                    if(res.subjectList[i].type==1){
                        type="客观题"
                    }else if(res.subjectList[i].type==2){
                        type="选择题"
                    }else{
                        type="编程题"
                    }
                    var cell='<tr><td>'+res.subjectList[i].id+'</td><td class="lang">'+res.subjectList[i].name+'</td><td>'+type+'</td><td>L0</td><td class="operate lang"><button class="edit">编辑</button><button class="del">删除</button><button class="look">查看</button></td></tr>'
                    data+=cell
                }
                document.getElementById("table_data").innerHTML = data
            }
        }
    })
}

window.onload = getQuestionList()

// 编辑
editBtn.onclick = edit;

// 删除
delBtn.onclick = del;

// 查看
lookBtn.onclick = look;