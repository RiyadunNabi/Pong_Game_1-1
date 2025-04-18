// Pong Game
// Developed by Carlos Yanez

/* Define Canvas */

var canvas;
var stage;

// Graphics
//[Background]

var bgImg = new Image();
var bg;

//[Title View]
 
var mainImg = new Image();
var main;
var startBImg = new Image();
var startB;
var creditsBImg = new Image();
var creditsB;

//[Title View Group]

var TitleView = new Container();

//[Credits]

var creditsViewImg = new Image();
var credits;

//[Game View]

var playerImg = new Image();
var player;
var ballImg = new Image();
var ball;
var cpuImg = new Image();
var cpu;
var winImg = new Image();
var win;
var loseImg = new Image();
var lose;

//[Score]

var playerScore;
var cpuScore;

// Variables

var xSpeed = 5;
var ySpeed = 5;
var gfxLoaded = 0;
var tkr = new Object;

// Main Function

function Main()
{
	/* Link Canvas */
	
	canvas = document.getElementById('Pong');
  	stage = new Stage(canvas);
  		
  	stage.mouseEventsEnabled = true;
  	
  	/* Sound */

	SoundJS.addBatch([
		{name:'hit', src:'hit.mp3', instances:1},
		{name:'playerScore', src:'playerScore.mp3', instances:1},
		{name:'enemyScore', src:'enemyScore.mp3', instances:1},
		{name:'wall', src:'wall.mp3', instances:1}]);
  		
  	/* Load GFX */
  		
  	bgImg.src = 'bg.png';
  	bgImg.name = 'bg';
  	bgImg.onload = loadGfx;
  	
  	mainImg.src = 'main.png';
  	mainImg.name = 'main';
  	mainImg.onload = loadGfx;
	
	startBImg.src = 'startB.png';
	startBImg.name = 'startB';
	startBImg.onload = loadGfx;
	
	creditsBImg.src = 'creditsB.png';
	creditsBImg.name = 'creditsB';
	creditsBImg.onload = loadGfx;
	
	creditsViewImg.src = 'credits.png';
	creditsViewImg.name = 'credits';
	creditsViewImg.onload = loadGfx;
	
	playerImg.src = 'paddle.png';
	playerImg.name = 'player';
	playerImg.onload = loadGfx;
	
	ballImg.src = 'ball.png';
	ballImg.name = 'ball';
	ballImg.onload = loadGfx;
	
	cpuImg.src = 'paddle.png';
	cpuImg.name = 'cpu';
	cpuImg.onload = loadGfx;
	
	winImg.src = 'win.png';
	winImg.name = 'win';
	winImg.onload = loadGfx;
	
	loseImg.src = 'lose.png';
	loseImg.name = 'lose';
	loseImg.onload = loadGfx;
	
	/* Ticker */
	
	Ticker.setFPS(30);
	Ticker.addListener(stage);
}

function loadGfx(e)
{
	if(e.target.name = 'bg'){bg = new Bitmap(bgImg);}
	if(e.target.name = 'main'){main = new Bitmap(mainImg);}
	if(e.target.name = 'startB'){startB = new Bitmap(startBImg);}
	if(e.target.name = 'creditsB'){creditsB = new Bitmap(creditsBImg);}
	if(e.target.name = 'credits'){credits = new Bitmap(creditsViewImg);}
	if(e.target.name = 'player'){player = new Bitmap(playerImg);}
	if(e.target.name = 'ball'){ball = new Bitmap(ballImg);}
	if(e.target.name = 'cpu'){cpu = new Bitmap(cpuImg);}
	if(e.target.name = 'win'){win = new Bitmap(winImg);}
	if(e.target.name = 'lose'){lose = new Bitmap(loseImg);}
	
	gfxLoaded++;
	
	if(gfxLoaded == 10)
	{
		addTitleView();
	}
}

// Add Title View Function

function addTitleView()
{
	startB.x = 240 - 31.5;
	startB.y = 160;
	startB.name = 'startB';
	
	creditsB.x = 241 - 42;
	creditsB.y = 200;
	
	TitleView.addChild(main, startB, creditsB);
	stage.addChild(bg, TitleView);
	stage.update();
	
	// Button Listeners
	
	//startB.onPress = tweenTitleView;
	creditsB.onPress = showCredits;
}

function showCredits()
{
	// Show Credits
		
	credits.x = 480;
		
	stage.addChild(credits);
	stage.update();
	Tween.get(credits).to({x:0}, 300);
	credits.onPress = hideCredits;
}

// Hide Credits

function hideCredits(e)
{
	Tween.get(credits).to({x:480}, 300).call(rmvCredits);
}

// Remove Credits

function rmvCredits()
{
	stage.removeChild(credits);
}