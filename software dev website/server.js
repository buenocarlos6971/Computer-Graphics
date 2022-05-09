var express = require('express');
var app = express();
var session = require('express-session');
// var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');

var pg = require('pg')
var pgSession = require('connect-pg-simple')(session);

var path = require('path');
const { request } = require('http');
const { query } = require('express');


app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));



var pgp = require('pg-promise')();


let dbConfig = {
	host: 'localhost',
	port: 5432,
	database: 'postgres',
	user: 'postgres',
	password: 'nizixuan0212'
};
var pgPool = new pg.Pool(dbConfig);
// var db = pgp(dbConfig);

const isProduction = process.env.NODE_ENV === 'production';
dbConfig = isProduction ? process.env.DATABASE_URL : dbConfig;
let db = pgp(dbConfig);

// app.use(bodyParser.json());
// app.use(bodyParser.urlencoded({ extended: true }));
// app.use(cookieParser());
// app.use(session({
// 	store: new pgSession({
// 	  pool : pgPool,                // Connection pool
// 	  tableName : 'session'   // Use another table-name than the default "session" one
// 	}),
// 	secret: `secret`,
// 	resave: false,
// 	cookie: { maxAge: 30 * 24 * 60 * 60 * 1000 } // 30 days
//   }));



app.set('view engine', 'ejs');
// app.set('views', path.join(__dirname, '/views/login '))
app.use(express.static(__dirname + '/'));

//login page
app.get('/', function (req, res) {
    res.render('login', {
        local_css: "style.css",
        my_title: "Login Page"
    });
});

app.get('/login', function (req, res) {
    res.render('login', {
        local_css: "style.css",
        my_title: "Login Page"
	});
});
 
//Home page
app.get('/home', function (req, res) {
 
			res.render('home', {
				local_css: "style.css",
				my_title: "Home Page"
			});

	
});

//profile page
app.get('/profile_page', function (req, res) {

			res.render('profile_page', {
				local_css: "style.css",
				my_title: "Profile Page"
			});
	
});


//login

app.post('/login/login', function(req, res) {
	const email = req.body.email;
    const password = req.body.password;
    const que = "SELECT * FROM users WHERE passw = '" + password + "' AND email = '" + email + "';";

    
		db.query(que).then((queryRows)=>{
			if (queryRows.length > 0){
                // request.session.user = row;

				res.redirect('/home');
			} else {
				res.send('Incorrect Password!');
			}
        });
        
});

//Audio Visualizer
app.get('/vis_final', function (req, res) {
    res.sendFile(__dirname + '/views/vis_final.html');

});




//sign up
app.post('/login/signup', function(req, res){
	var fName = req.body.first_name;
	// var lName = req.body.last_name;
	var emaiL = req.body.email;
	var pass = req.body.passw;
    console.log(fName);
	// console.log(emaiL);
	// console.log(pass);
    
    var insertQ = "INSERT INTO users(first_name, last_name, passw, email) VALUES ('"+fName+"', 'test', '"+pass+"' , '"+emaiL+"')";
    
    db.task('sign up', task => {
		return task.batch([
			task.any(insertQ)
		]);
	})
	.then(data => {
		// res.render('login', {
		// 	local_css: "style.css",
		// 	my_title: "Login Page"
		// });

	})
	.catch(err => {
		console.log('error', err);
		// res.render('login', {
		// 	local_css: "style.css",
		// 	my_title: "Login Page"
		// })
	})
    res.redirect('/login');
});



// app.listen(3000);
// console.log('Connected to server.js');

const PORT = process.env.PORT || 8080;

const server = app.listen(PORT, () => {
	console.log(`Express running → PORT ${server.address().port}`);
});
