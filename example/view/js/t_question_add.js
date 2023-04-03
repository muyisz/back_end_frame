let pro = document.querySelector(".program_question");
let obj = document.querySelector(".objective_question");
let cho = document.querySelector(".choice_question");

let selectObj = document.getElementById('question_type');

selectObj.onchange = function () {
    //获取选中项的索引
    let index = selectObj.selectedIndex;
    console.log(index);

    //获取选中项的文本
    let text = selectObj.options[index].text;
    console.log(text);

    //获取选中项的value值
    let value = selectObj.options[index].value;
    console.log(value);

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