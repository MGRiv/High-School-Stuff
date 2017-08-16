# Refactoring... 

## Team
| Name       | Role            |
|------------|-----------------|
|Rothblatt, David  | Leader          |
|Spektor, Nellie | UX              |
|Rivera, Michael | Backend         |
|Redozubov, Greg | Middleware      |

------------------------------------------------------

#<img src="https://raw.githubusercontent.com/alex-wyc/Untitled/master/static/Logo%20With%20Title.png" height="45px" alt-text = "Logo Text">
Project for Software Development Class -- Crowd-Writing Story Engine

> I wanted a perfect ending. Now I've learned, the hard way,
> that some poems don't rhyme, and some stories don't have a clear beginning,
> middle, and end.Life is about not knowing, having to change, taking the moment
> and making the best of it, without knowing what's going to happen next.
> Delicious Ambiguity.
>
> -Gilda Radner

## Installation
Make sure you have flask and sqlite3 installed, then simply run
```bash
python app.py
```

For more options, run
```bash
python app.py -h
```

## Team
| Name       | Role            |
|------------|-----------------|
|Yicheng W.  | Leader          |
|Felicity N. | UX              |
|Michael M.  | Backend         |
|Sally B.    | Middleware      |

## Description
This is a crowd-writing engine in which everyone can contribute to a story. In
this place, everyone can create their own stories or edit someone else's existing work. However, the catch is that one person can only enter 140
characters (or 300 if they're creating a story) at a time. This way, the
final story will be an interesting mix of different people's inputs.

The site also allows individual users to favorite or bookmark stories they like
and get updates about them in their home page.

## Design and Toolset
### Backend
This project was built with sqlite3 and flask on the back end. It has 3 main
data-tables, one holding stories, one holding the users, and one holding the
favorites.

Each story is assigned an ID number. The stories data table has columns id,
sentence, author and time. Whever an author adds a new sentence, a new row is
added into the stories data table. The story is then gathered by sorting all
sentences by time stamp, with the first sentence being the title, and
everything else making up the story.

The favorites data table has columns for user and story id, and it's just simple
lookup/addition/deletion to check/add/remove favorites.

The user data table is pretty standard, with columns for username and for password hashes.

### Frontend
The front end of the project is built with jinja2, bootstrap and jQuery. There
is a master html which makes up the heading and is extended by every other page.
For the most part is is pretty standard.

#### Routes
- home
- about
- login/logout
- register
- browse
- create
- edit
- favorite

## Development Log
- [x] 2015-10-13: Finsih overarching design, finish login system
- [x] 2015-10-14: Finish setting datatable
- [x] 2015-10-15: Finish adding stories
- [x] 2015-10-16: Create favorite system
- [x] 2015-10-17: Finish favorite
- [x] 2015-10-18: PENTEST
- [x] 2015-10-19: Demo

## TODO
- [ ] Add privilaged (admin) level users
- [ ] Add ability to sort by number of favorites
- [ ] Add more info to browse (last time edited/num of people who favorited a story/length of a story)
- [ ] Add user level by chars contributed
- [ ] Add SOME styling to edit (newline, new paragraphs)
