let component = ReasonReact.statelessComponent("FriendsList");

type friend = {
  id: int,
  name: string,
  age: int,
  email: string,
};

[@genType]
let make = (~data, _children) => {
  ...component,
  render: _self => {
    <ul>
      {data
       |> Js.Array.map((d: friend) =>
            <li key={d.id |> string_of_int}>
              <div> {d.name |> ReasonReact.string} </div>
              <div> {d.age |> string_of_int |> ReasonReact.string} </div>
              <div> {d.email |> ReasonReact.string} </div>
            </li>
          )
       |> ReasonReact.array}
    </ul>;
  },
};