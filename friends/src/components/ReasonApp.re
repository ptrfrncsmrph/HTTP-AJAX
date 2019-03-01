[%bs.raw {| require("./App.scss") |}];

open FriendsList;

type state =
  | Loading
  | Error(Js.Promise.error)
  | Loaded(Js.Array.t(friend));

type editingState =
  | EditingExistent(friend)
  | EditingNew;

let emptyFriend: FriendForm.unvalidatedFriend = {
  name: "",
  email: "",
  age: "",
  id: None,
};

type action =
  | GetFriends
  | FriendsGot(Js.Array.t(friend))
  | PostFriend(FriendForm.unvalidatedFriend)
  | PutFriend(int, FriendForm.unvalidatedFriend)
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

  initialState: _state => (Loading, EditingNew),

  reducer: (action, _state) => {
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
    | PostFriend(_) => ReasonReact.NoUpdate
    | PutFriend(_, _) => ReasonReact.NoUpdate
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
       | (Loaded(data), EditingNew) =>
         <>
           <FriendsList data />
           <FriendForm
             friend=emptyFriend
             handleSubmit={f => send(PostFriend(f))}
           />
         </>
       | (Loaded(data), EditingExistent(_)) =>
         <>
           <FriendsList data />
           <FriendForm
             handleSubmit={f => send(PostFriend(f))}
             friend=emptyFriend
           />
         </>
       | (Error(_err), _) => <div> {"Error" |> ReasonReact.string} </div>
       }}
    </main>;
  },
};

let jsComponent =
  ReasonReact.wrapReasonForJs(~component, _jsProps => make([||]));