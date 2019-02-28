type state =
  | Loading
  | Error
  | Loaded(Js.Array.t(FriendsList.friend));

type action =
  | GetFriends
  | FriendsGot(Js.Array.t(FriendsList.friend))
  | PostFriend(FriendForm.unvalidatedFriend)
  | PutFriend(int, FriendForm.unvalidatedFriend)
  | DeleteFriend(int)
  | ShowError;

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
        self => {
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
                     //  |> Json.parseOrRaise
                     |> Json.Decode.(array(Decode.friend))
                     |> (fs => self.send(FriendsGot(fs)))
                     |> resolve
                 )
               )
            |> catch(err => err |> Js.log |> resolve)
          );
          ();
        },
      )
    | FriendsGot(fs) => ReasonReact.Update(Loaded(fs))
    };
  },

  didMount: ({send}) => {
    send(GetFriends);
  },

  render: ({state, send}) => {
    switch (state) {
    | Loading => <div> {"Loading" |> ReasonReact.string} </div>
    | Loaded(data) => <FriendsList data />
    };
  },
};

let jsComponent =
  ReasonReact.wrapReasonForJs(~component, _jsProps => make([||]));