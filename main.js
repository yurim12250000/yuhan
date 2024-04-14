var canvas = document.getElementById("GameScreenCanvas");
var ctx = canvas.getContext("2d");

var redHues = ['#FF5733', '#FF6F61', '#FF7F50', '#F08080', '#E9967A', '#FA8072', '#FFA07A', '#FFA500'];
var pinkHues = ['#FFC0CB', '#FF69B4', '#FFB6C1', '#FF1493', '#DB7093', '#FFA07A', '#FF7F7F', '#FFD700'];

// 하트 객체를 정의하는 클래스
class HeartObject {
    constructor(x, y, color, size, speed) {
        this.x = x; // x 좌표
        this.y = y; // y 좌표
        this.color = color; // 색상
        this.size = size; // 크기
        this.speed = speed; // 속도
        this.direction = Math.random() * Math.PI * 2; // 랜덤한 이동 방향 (0부터 2파이 사이의 랜덤한 각도)
    }

    draw() {
        //원1
        ctx.beginPath();
        for (var i = 0; i <= 360; i++) {
            var x = this.x + Math.cos(Math.PI / 180 * i) * this.size;
            var y = this.y + Math.sin(Math.PI / 180 * i) * this.size;
            ctx.lineTo(x, y);
        }
        ctx.fillStyle = this.color;
        ctx.fill();
        ctx.closePath();

        //원2
        ctx.beginPath();
        for (var i = 0; i <= 360; i++) {
            var x = this.x + Math.cos(Math.PI / 180 * i) * this.size + this.size * 1.15;
            var y = this.y + Math.sin(Math.PI / 180 * i) * this.size;
            ctx.lineTo(x, y);
        }
        ctx.fillStyle = this.color;
        ctx.fill();
        ctx.closePath();

        //삼각형
        ctx.beginPath();
        ctx.moveTo(this.x - 30 * this.size / 50, this.y + 40 * this.size / 50);
        ctx.lineTo(this.x + 33 * this.size / 50, this.y + 85 * this.size / 50);
        ctx.lineTo(this.x + 88 * this.size / 50, this.y + 40 * this.size / 50);
        ctx.fillStyle = this.color;
        ctx.fill();
        ctx.closePath();
    }

    update() {
        //새로운 x,y 위치 계산
        this.x += Math.cos(this.direction) * this.speed; 
        this.y += Math.sin(this.direction) * this.speed;
    }
}

//하트 저장 배열
var hearts = [];

canvas.addEventListener("mousemove", function(event) {
    var x = event.clientX - canvas.getBoundingClientRect().left; //x 좌표
    var y = event.clientY - canvas.getBoundingClientRect().top; //y 좌표
    var color;
    
    // 랜덤 색상 선택
    if (Math.random() < 0.5) {
        color = redHues[Math.floor(Math.random() * redHues.length)];
    } else {
        color = pinkHues[Math.floor(Math.random() * pinkHues.length)];
    }
    
    // 랜덤 크기와 속도 선택
    var size = Math.random() * 50 + 20;
    var speed = Math.random() * 3 + 1;
    
    // 하트 객체 생성 및 배열에 추가
    var heart = new HeartObject(x, y, color, size, speed);
    hearts.push(heart);
});

// 하트를 그리고 이동시키는 함수
function drawAndMoveHearts() {
    ctx.clearRect(0, 0, canvas.width, canvas.height); // 캔버스 지우기
    for (var i = 0; i < hearts.length; i++) {
        hearts[i].draw(); // 하트 그리기
        hearts[i].update(); // 하트 위치 업데이트
        if (hearts[i].x < -100 || hearts[i].x > canvas.width + 100 || hearts[i].y < -100 || hearts[i].y > canvas.height + 100) {
            hearts.splice(i, 1); // 하트가 캔버스 밖으로 벗어나면 없앰
            i--;
        }
    }
    requestAnimationFrame(drawAndMoveHearts); 
}

drawAndMoveHearts();