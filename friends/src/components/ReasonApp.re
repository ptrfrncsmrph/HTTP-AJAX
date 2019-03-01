[%bs.raw {| require("./App.scss") |}];

open FriendsList;

type state =
  | Loading
  | Error(Js.Promise.error)
  | Loaded(Js.Array.t(friend));

type editingState =
  | EditingExistent(friend)
  | EditingNew;

type action =
  | GetFriends
  | FriendsGot(Js.Array.t(friend))
  | PostFriend(FriendForm.validatedFriend)
  | EditFriend(friend)
  | PutFriend(int, FriendForm.validatedFriend)
  | DeleteFriend(int)
  | GotError(Js.Promise.error);

module Decode = {
  let friend = json =>
    Json.Decode.{
      name: json |> field("name", string),
      age: json |> field("age", int),
      email: json |> field("email", string),
      id: json |> field("id", int),
    };
};

let apiEndpoint = "http://10.0.0.53:5000/friends";

let component = ReasonReact.reducerComponent("ReasonApp");

let make = _children => {
  ...component,

  initialState: () => (Loading, EditingNew),

  reducer: (action, (s, _e)) => {
    switch (action) {
    | GetFriends =>
      ReasonReact.UpdateWithSideEffects(
        (Loading, EditingNew),
        ({send}) =>
          Js.Promise.(
            Axios.get(apiEndpoint)
            |> then_(response =>
                 response##data
                 |> Json.Decode.(array(Decode.friend))
                 |> (fs => send(FriendsGot(fs)))
                 |> resolve
               )
            |> catch(err => send(GotError(err)) |> resolve)
            |> ignore
          ),
      )
    | FriendsGot(fs) => ReasonReact.Update((Loaded(fs), EditingNew))
    | PostFriend(f) =>
      ReasonReact.UpdateWithSideEffects(
        (s, EditingNew),
        ({send}) =>
          Js.Promise.(
            Axios.postData(apiEndpoint, FriendForm.validatedFriendToJs(f))
            |> then_(response =>
                 response##data
                 |> Json.Decode.(array(Decode.friend))
                 |> (fs => send(FriendsGot(fs)))
                 |> resolve
               )
            |> catch(err => send(GotError(err)) |> resolve)
            |> ignore
          ),
      )
    | EditFriend(f) => ReasonReact.Update((s, EditingExistent(f)))
    | PutFriend(id, f) =>
      ReasonReact.UpdateWithSideEffects(
        (s, EditingNew),
        ({send}) =>
          Js.Promise.(
            Axios.putData(
              apiEndpoint ++ "/" ++ string_of_int(id),
              FriendForm.validatedFriendToJs(f),
            )
            |> then_(response =>
                 response##data
                 |> Json.Decode.(array(Decode.friend))
                 |> (fs => send(FriendsGot(fs)))
                 |> resolve
               )
            |> catch(err => send(GotError(err)) |> resolve)
            |> ignore
          ),
      )
    | DeleteFriend(_) => ReasonReact.NoUpdate
    | GotError(err) => ReasonReact.Update((Error(err), EditingNew))
    };
  },

  didMount: ({send}) => {
    send(GetFriends);
  },

  render: ({state, send}) => {
    <main className="App">
      {switch (state) {
       | (Loading, _) => <div> {"Loading" |> ReasonReact.string} </div>
       | (Loaded(data), e) =>
         <>
           <FriendsList data handleEdit={f => send(EditFriend(f))} />
           {switch (e) {
            | EditingExistent(f) =>
              <FriendForm
                initState={FriendForm.toUnvalidated(f)}
                handleSubmit={({name, age: age_, email}) =>
                  send(
                    PutFriend(
                      f.id,
                      {name, age: int_of_string(age_), email},
                    ),
                  )
                }
              />
            | EditingNew =>
              <FriendForm
                handleSubmit={({name, age: age_, email}) =>
                  send(PostFriend({name, age: int_of_string(age_), email}))
                }
              />
            }}
         </>
       | (Error(_err), _) => <div> {"Error" |> ReasonReact.string} </div>
       }}
    </main>;
  },
};

let jsComponent =
  ReasonReact.wrapReasonForJs(~component, _jsProps => make([||]));