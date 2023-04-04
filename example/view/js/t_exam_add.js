let addBtn = document.querySelector(".addBtn");
let addBox = document.querySelector(".add");
let autoBtn = document.querySelector(".autoBtn");

// 每一个题目后面都有一个按钮，此处使用querySelectorAll获取，返回的是一个伪数组(元素集合)，使用时可以使用对应的下标，或者修改此获取方法
let choiceBtn = document.querySelectorAll(".choiceBtn");

// .add 盒子显示
function boxShow() {
    addBox.style.display = "block";
}

// 添加题目按钮点击后题目列表出现
addBtn.onclick = boxShow;

// 第一个“选择” 按钮  手动生成
function choice() {

}

// 第一个“选择” 按钮  手动生成
choiceBtn[0].onclick = choice;

// "自动生成" 按钮
function auto() {
    
}

// “自动生成” 按钮
autoBtn.onclick = auto;