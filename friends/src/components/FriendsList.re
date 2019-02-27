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
              {d.name |> ReasonReact.string}
            </li>
          )
       |> ReasonReact.array}
    </ul>;
  },
};