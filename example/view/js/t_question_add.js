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
    
}

// 创建按钮
creBtn.onclick = create;