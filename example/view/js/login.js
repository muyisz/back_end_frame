let loginBtn = document.querySelector(".login");
let registerBtn = document.querySelector(".register");

// "登录" 按钮
loginBtn.onclick = login;

// "注册" 按钮
registerBtn.onclick = register;

// "登录" 按钮
function login() {
    let postData={
        id:$('#account').val(),
        password:$('#password').val(),
        type: parseInt($('input:radio[name="status"]:checked').val())
    }
    $.ajax({
        type: 'post',
        url: '/login',
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

// "注册" 按钮
function register() {
    window.location.href = '/regester'
}
