let pro = document.querySelector(".program_question");
let obj = document.querySelector(".objective_question");
let cho = document.querySelector(".choice_question");

// 创建按钮
let creBtn = document.querySelector(".creBtn");

// 获取题目类型的下拉列表
let selectObj = document.getElementById('question_type');

// 切换题目选项卡
selectObj.onchange = function () {
    //获取选中项的索引
    let index = selectObj.selectedIndex;

    //获取选中项的value值
    let value = selectObj.options[index].value;

    switch (value) {
        case "1":
            console.log('成功');
            pro.classList.remove("hidden");
            obj.classList.add("hidden");
            cho.classList.add("hidden");
            break;
        case "2":
            console.log('成功');
            pro.classList.add("hidden");
            obj.classList.remove("hidden");
            cho.classList.add("hidden");
            break;
        case "3":
            console.log('成功');
            pro.classList.add("hidden");
            obj.classList.add("hidden");
            cho.classList.remove("hidden");
            break;
    }
}

// 创建按钮
function create() {
    let index = selectObj.selectedIndex;
    let value = selectObj.options[index].value;
    var type = 0;
    switch (value) {
        case "1":
            type = 3;
            break;
        case "2":
            type = 1;
            break;
        case "3":
            type = 2;
            break;
    }
    var postData

    if(type==3){
        let test={
            in: $('#test_in').val(),
            out: $('#test_out').val(),
        }

        let data={
            in: $('#data_in').val(),
            out: $('#data_out').val(),
        }

        postData = {
            name: $('#name').val(),
            content: $('#content').val(),
            type: type,
            test: test,
            data: [data],
        }

    }else if(type==2){
        postData = {
            name: $('#name').val(),
            content: $('#content').val(),
            type: type,
            answer:$('#anwser2').val()
        }
    }else{
        postData = {
            name: $('#name').val(),
            content: $('#content').val(),
            type: type,
            answer:$('#anwser1').val()
        }
    }

    $.ajax({
        type: 'post',
        url: '/subject/create',
        dataType: 'json',
        data: JSON.stringify(postData),
        success: function (res) {
            if(res.code!=0){
                alert(res.message)
            }else{
               window.location.href = '/subject/list_pages'
            }
        }
    })
}

// 创建按钮
creBtn.onclick = create;