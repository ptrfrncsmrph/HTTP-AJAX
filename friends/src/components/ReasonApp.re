type state =
  | Loading
  | Error
  | Loaded(Js.Array.t(FriendsList.friend));

type action =
  | GetFriends
  | PostFriend(FriendForm.unvalidatedFriend)
  | PutFriend(int, FriendForm.unvalidatedFriend)
  | DeleteFriend(int)
  | ShowError;

let component = ReasonReact.reducerComponent("ReasonApp");

let make = _children => {
  ...component,

  initialState: _state => Loading,

  reducer: action => {
    switch (action) {
    | GetFriends =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
        self =>
          Js.Promise.(
            Axios.get("/user?ID=12345")
            |> then_(response => resolve(Js.log(response##data)))
            |> catch(error => resolve(Js.log(error)))
          ),
      )
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