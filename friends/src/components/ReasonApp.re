type state =
  | Loading
  | Error(Js.Promise.error)
  | Loaded(Js.Array.t(FriendsList.friend));

type action =
  | GetFriends
  | FriendsGot(Js.Array.t(FriendsList.friend))
  | PostFriend(FriendForm.unvalidatedFriend)
  | PutFriend(int, FriendForm.unvalidatedFriend)
  | DeleteFriend(int)
  | GotError(Js.Promise.error);

open FriendsList;

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

  initialState: _state => Loading,

  reducer: (action, _state) => {
    switch (action) {
    | GetFriends =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
        ({send}) =>
          Js.Promise.(
            Axios.get(apiEndpoint)
            |> then_(response =>
                 response##data
                 |> (
                   data =>
                     {
                       Js.log(data);
                       data;
                     }
                     |> Json.Decode.(array(Decode.friend))
                     |> (fs => send(FriendsGot(fs)))
                     |> resolve
                 )
               )
            |> catch(err => send(GotError(err)) |> resolve)
            |> ignore
          ),
      )
    | FriendsGot(fs) => ReasonReact.Update(Loaded(fs))
    | PostFriend(_) => ReasonReact.NoUpdate
    | PutFriend(_, _) => ReasonReact.NoUpdate
    | DeleteFriend(_) => ReasonReact.NoUpdate
    | GotError(err) => ReasonReact.Update(Error(err))
    };
  },

  didMount: ({send}) => {
    send(GetFriends);
  },

  render: ({state, send}) => {
    switch (state) {
    | Loading => <div> {"Loading" |> ReasonReact.string} </div>
    | Loaded(data) => <FriendsList data />
    | Error(_err) => <div> {"Error" |> ReasonReact.string} </div>
    };
  },
};

let jsComponent =
  ReasonReact.wrapReasonForJs(~component, _jsProps => make([||]));