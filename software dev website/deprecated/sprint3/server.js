/*****
 * This is the start if the node.js for the project. This temp[late was copied from Lab 9
 */
var express = require('express'); //Ensure our express framework has been added
var app = express();
var bodyParser = require('body-parser'); //Ensure our body-parser tool has been added
app.use(bodyParser.json());              // support json encoded bodies
app.use(bodyParser.urlencoded({ extended: true })); // support encoded bodies

//Create Database Connection
var pgp = require('pg-promise')();

/**********************
  Database Connection information
  host: This defines the ip address of the server hosting our database.  We'll be using localhost and run our database on our local machine (i.e. can't be access via the Internet)
  port: This defines what port we can expect to communicate to our database.  We'll use 5432 to talk with PostgreSQL
  database: This is the name of our specific database.  From our previous lab, we created the football_db database, which holds our football data tables
  user: This should be left as postgres, the default user account created when PostgreSQL was installed
  password: This the password for accessing the database.  You'll need to set a password USING THE PSQL TERMINAL THIS IS NOT A PASSWORD FOR POSTGRES USER ACCOUNT IN LINUX!
**********************/
const dbConfig = {
    host: 'localhost',
    port: 5432,
    database: 'football_db',
    user: 'postgres',
    password: 'NAP'
};

var db = pgp(dbConfig);

// set the view engine to ejs
app.set('view engine', 'ejs');
app.use(express.static(__dirname + '/'));//This line is necessary for us to use relative paths and access our resources directory





// login page 
app.get('/', function (req, res) {
    res.render('pages/login', {
        local_css: "signin.css",
        my_title: "Login Page"
    });
});

// registration page 
app.get('/register', function (req, res) {
    res.render('pages/register', {
        my_title: "Registration Page"
    });
});

/*Add your other get/post request handlers below here: */
app.get('/home', function (req, res) {
    var query = 'select song_name from Favorite;';
    db.any(query)
        .then(function (rows) {
            res.render('pages/home', {
                my_title: "Home Page",
                data: rows,
                color: '',
                color_msg: ''
            })

        })
        .catch(function (err) {
            console.log('error', err);
            res.render('pages/home', {
                my_title: 'Home Page',
                data: '',
                color: '',
                color_msg: ''
            })
        })
});
app.get('/home/pick_color', function (req, res) {
    var song_choice = req.query.song_selection;
    var song_options = "SELECT * FROM Favorite;";
    var song_author = "SELECT song_author FROM Favorite WHERE ID = '" + song_choice + "';";
    db.task('get-everything', task => {
        return task.batch([
            task.any(song_options),
            task.any(song_author)
        ]);
    })
        .then(info => {
            res.render('pages/home', {
                my_title: "Home Page",
                data: info[0],
                song: song_choice,
                author: info[1][0].song_author
            })
        })
        .catch(err => {
            console.log('error', err);
            res.render('pages/home', {
                my_title: 'Home Page',
                data: '',
                color: '',
                color_msg: ''
            })
        });

});

app.post('/home/pick_song', function (req, res) {
    var song_id = req.body.song_choice.ID;
    var song_name = req.body.song_choice.song_name;
    var song_author = req.body.song_choice.song_author;
    var postTitle = req.body.title;
    var postBody = req.body.caption;
    var insertPost = "INSERT INTO Post(post_title, post_body) VALUES('" + postTitle + "' , '" + postBody + "');";
    var insert_song_statement = "INSERT INTO Favorite(ID, song_name, song_author) VALUES('" + song_id + "', '" + song_name + "', '" + song_author + "');";
    var song_select = "SELECT * FROM Favorite;";

    db.task('get-everything', task => {
        return task.batch([
            task.any(insertPost),
            task.any(insert_song_statement),
            task.any(song_select),

        ]);
    })
        .then(info => {
            res.render('pages/home', {
                my_title: "Home Page",
                data: info[2],
                song: song_name,
                songA: song_author,// Return the hex value of the color added to the table
                pBody: postBody,
                pInsert: info[0],
                sInsert: info[1] // Return the color message of the color added to the table
            })
        })
        .catch(err => {
            console.log('error', err);
            res.render('pages/home', {
                my_title: 'Home Page',
                data: '',
                song: '',
                songA: '',// Return the hex value of the color added to the table
                pBody: '',
                pInsert: '',
                sInsert: ''
            })
        });
});
/*This is for returning user informantion 
*/
app.get('/login', function (req, res) {
    var getUser = "SELECT * FROM users;";
  
    db.task('get-everything', task => {
        return task.batch([
            task.any(getUser),
            
        ]);
    })
        .then(data => {
            res.render('pages/team_stats', {
                my_title: "Page Title Here",
                user: data[0],
                
            })
        })
        .catch(err => {
            // display error message in case an error
            console.log('error', err);
            res.render('pages/team_stats', {
                my_title: "Page Title Here",
                user: ''
            })
        });
});
/** Add a new user to the database */
app.get('/login/addnew', function (req, res) {
    var newUEmail = req.body.email;
    var newUFirstName = req.body.firstName;
    var newUlastName = req.body.lastname;
    var newUpassword = req.body.password;
    var newUserInsert = "INSERT INTO users(first_name, last_name, password, Email) VALUES('"+newUFirstName+"', '"+newUlastName+"', '"+newUpassword+"', '"+newUEmail+"');";
    db.task('get-everything', task => {
        return task.batch([
            task.any(newUserInsert),
            
            

        ]);
    })
        .then(info => {
            res.render('pages/home', {
                my_title: "Home Page",
                data: info[0],
                email: newUEmail,
                fistName: newUFirstName,
                lastName: newUlastName,
                pass: newUpassword

            })
        })
        .catch(err => {
            console.log('error', err);
            res.render('pages/home', {
                my_title: 'Home Page',
                data: '',
                email: '',
                fistName: '',
                lastName: '',
                pass: ''
            })
        });
});

/** to get past posts for a user */
app.get('/login/info', function (req, res) {
    var postId = req.body.post.ID;
   var post= "SELECT * FROM post;";
   var songs ="SELECT * FROM Favorite INNER JOIN post on post.PostID = Favorite.ID;";
    db.task('get-everything', task => {
        return task.batch([
            task.any(post),
            task.any(songs),
           
        ]);
    })
        .then(info => {

            res.render('/pages/login/info', {
                my_title: "post Info",
                data: info[0],
                data2: info[1],
                IDpost: postID
                
            })
        })
        .catch(error => {

            console.log(error);
            res.render('pages/login/info', {
                my_title: "post Info",
                data: '',
                data2: '',
                IDpost: ''

            })
        });
});

app.get('/login', function (req, res) {
    var email = req.query.email;
    var pswd= req.query.password;
    var email_options = "SELECT email FROM Users;";
    var pswd_options ="SELECT password FROM Users;";
    db.task('get-everything', task => {
        return task.batch([
            task.any(email_options),
            task.any(pswd_options)
        ]);
    })
        .then(info => {
            res.render('/login', {
                my_title: "Login Page",
                data: info[0],
                email: email_options,
                password: info[1][0].pswd_options
            })
        })
        .catch(err => {
            console.log('error', err);
            res.render('/login', {
                my_title: 'Login Page',
                data: '',
                email: '',
                password: ''
            })
        });

});

app.listen(3000);
console.log('3000 is the magic port');