


To-Do:

    - Agree on a workflow. 
        - Local machine -- Github -- server.
        - cLion. terminal. git. git commands. github desktop. database.

    - Propose basic Git SOP:
        - Protect github repo's main branch
        - no: git add .  --- (Always check before hand what you are pushing)
        - Create appropriate branches. 
        - main "protections" -- pull requests.

    - We should all be on the same page with:
        - Understanding server client reltion. 
        - Apache(How apache routes to files). Get/Post. How the .CGI files work/execute.
        - just the overall expectations for the assignment and how it all pulls together

    - Then we ought to assign tasks to members based off task dependencies. So we know who owns what. 



Here's an example repo layout that I got from ChatGPT.

Again, just an example, but something that we should be aware of and discuss: 

auction-site/
├─ README.md
├─ .gitignore
│
├─ docs/                            (design notes, diagrams, API notes)
│  ├─ schema.md
│  ├─ endpoints.md
│  └─ setup-blue.md
│
├─ sql/                             (database stuff)
│  ├─ schema.sql                    (CREATE TABLEs)
│  ├─ seed.sql                      (optional test data)
│  └─ reset.sql                     (drop + recreate for dev)
│
├─ web/                             (things Apache serves directly)
│  ├─ index.html
│  ├─ login.html
│  ├─ register.html
│  ├─ css/
│  │  └─ style.css
│  ├─ js/
│  │  └─ main.js                    (optional)
│  └─ assets/
│     └─ logo.png                   (optional)
│
├─ cgi/                             (C++ sources for CGI binaries)
│  ├─ src/
│  │  ├─ login.cpp
│  │  ├─ logout.cpp
│  │  ├─ profile.cpp
│  │  ├─ transactions.cpp
│  │  ├─ auctions.cpp               (list/unexpired auctions)
│  │  ├─ bid.cpp
│  │  └─ create_auction.cpp
│  │
│  ├─ include/
│  │  ├─ cgi_request.hpp            (parse GET/POST, url-decode)
│  │  ├─ html.hpp                   (helpers to print HTML safely)
│  │  ├─ db.hpp                     (MySQL connection + queries)
│  │  ├─ session.hpp                (create/validate sessions)
│  │  └─ config.hpp                 (reads config file/env; no secrets committed)
│  │
│  └─ templates/                    (optional: header/footer partials)
│     ├─ header.html
│     └─ footer.html
│
├─ scripts/                         (developer scripts)
│  ├─ build.sh                      (compile on Blue)
│  ├─ deploy.sh                     (copy web/ + cgi binaries into ~/public_html)
│  └─ fmt.sh                        (optional clang-format)
│
├─ build/                           (generated binaries; gitignored)
│
└─ .env.example                     (shows needed vars; no real creds)


