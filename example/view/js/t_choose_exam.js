let beginBtn = document.querySelector(".begin");

// “开始考试” 按钮
function begin() {
    
}

// “开始考试” 按钮
beginBtn.onclick = begin;

function chooseExam(id){
    window.location.href = '/test_paper/test_pages?id='+id
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
                    var cell='<tr><td>xxx</td><td>'+res.testPaperList[i].id+'</td><td>'+res.testPaperList[i].facilityValue+'</td><td>'+res.testPaperList[i].creater+'</td><td class="operate"><button onclick="chooseExam('+res.testPaperList[i].id+')">开始考试</button></td></tr>'
                    data+=cell
                }
                document.getElementById("examList").innerHTML = data
            }
        }
    })
}

window.onload = getExamList()